#ifndef GAME_EVENT_LISTENER_H
#define GAME_EVENT_LISTENER_H

#include "cocos2d.h"
namespace tsg {
    namespace game {
        class IGameEventListener{
        public:
            virtual void onInit(cocos2d::Scene *) = 0;
            virtual ~IGameEventListener(){};
        };    
    }
}

#endif // GAME_EVENT_LISTENER_H

