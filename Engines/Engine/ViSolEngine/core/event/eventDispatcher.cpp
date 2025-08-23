#include"eventDispatcher.h"
/*4*/
namespace ViSolEngine {
    
    EventDispatcher::EventDispatcher() : mEventActionMap() {

	}

	EventDispatcher::~EventDispatcher() {
		for (auto& pair : mEventActionMap) {
			for (auto evenAction : pair.second) {
				VISOL_FREE_MEMORY(evenAction);
			}
			pair.second.clear();
		}
		mEventActionMap.clear();
	}
    
}

