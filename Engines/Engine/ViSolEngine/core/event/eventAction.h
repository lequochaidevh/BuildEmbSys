#pragma once
/*2*/
#include "eventContext.h"

namespace ViSolEngine {
	template<typename T> using eventCallback = std::function<bool(const T&)>;

	class VISOL_API IEventAction {
	public:
		virtual ~IEventAction() = default;
		virtual bool execute(const EventContext*) = 0;
	};

	template <typename T>
	class VISOL_API EventAction : public IEventAction {
	public:
		// add mCallback: eventCallback<T>
		EventAction(const eventCallback<T>& callback) : mCallback(callback){}
		virtual bool execute(const EventContext* eventContext) override {
			// check type value of eventContext
			VISOL_STATIC_ASSERT(std::is_base_of<EventContext, T>::value && "Invalid EventContext");
			// get value of casting pointer
			return mCallback(*(T*)eventContext);
		}

	private:
		eventCallback<T> mCallback;
	};
}