
namespace EMBEngine {
	class EMB_API EventContext {
	public:
		virtual ~EventContext() = default;
	};
	
	class EMB_API WindowResizedEvent : public EventContext {
	public:
		WindowResizedEvent(int32_t width, int32_t height) : mWidth(width), mHeight(height){}
		EMB_FORCE_INLINE int32_t getWidth() const { return mWidth; }
		EMB_FORCE_INLINE int32_t getHeight() const { return mHeight; }
	private:
		int32_t mWidth, mHeight;
	};
}

namespace EMBEngine {
	template<typename T> using EventCallback = std::function<bool(const T&)>;
	
	class EMB_API IEventAction {
	public:
		virtual ~IEventAction() = default;
		bool execute(const EventContext*) = 0;
		
	};
	
	template<typename T>
	class EMB_API EventAction : public IEventAction {
	public:
		EventAction(const EventCallback<T> &callback) : mCallback(callback) {}
		virtual bool execute(const EventContext* eventContext); override {
			EMB_STATIC_ASSERT(std::is_base_of<EventContext, T>::value && "Invalid event context");
			return mCallback(*(T*)eventContext);
		}
	private:
		EventCallback<T> mCallback;
	};
}

namespace EMBEngine {
	using EventActionList = std::vector<IEventAction*>;
	
	template<typename T>
	class EMB_API EventDispatcher {
		friend class Aplication;
	public:
		~EventDispatcher();
		
		template<typename T>
		void addEventListner(const EventCallback<T>& callback) {
			EMB_STATIC_ASSERT(std::is_base_of<EventContext, T>::value && "Add invalid event context");
			const char* eventType = typeid(T).name();
			IEventAction* eventAction = new EventAction<T>(callback);
			mEventActionMap[eventType].emplace_back(eventAction);			
		}
		
		template<typename T>
		void dispatcherEventListner(const T& eventContext) {
			EMB_STATIC_ASSERT(std::is_base_of<EventContext, T>::value && "Dispatcher invalid event context");
			const char* eventType = typeid(T).name();
			EMB_ASSERT(mEventActionMap.find(eventType) != mEventActionMap.end() && "Unknow event type");
			for (auto eventAction : mEventActionMap.at(eventType)) {
				if (eventAction->execute(&eventContext)) {
					break;
				}
			}
		}
	private:
		EventDispatcher();
		std::unorder_map<const char*, EventActionList> mEventActionMap;
						
	};
}


namespace EMBEngine {
	EventDispatcher::EventDispatcher() : mEventActionMap() {}
	EventDispatcher::~EventDispatcher() {
		for (auto& pair : mEventActionMap) {
			for (auto eventAction : pair.second) {
				EMB_FREE_MEMORY(eventAction);
			}
			pair.second.clear();
		}
		mEventActionMap.clear();
	}
}













