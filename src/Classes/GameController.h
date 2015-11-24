#ifndef __GAMECONTROLLER_H__
#define __GAMECONTROLLER_H__

#include "MapController.h"
#include "MoveController.h"
#include "IGameEventListener.h"

#include "cocos2d.h"

namespace tsg {
    namespace game{
        /*
         Manages game components
         */
        class GameController : public cocos2d::Layer {
        private:
            map::MapController * mapController;
            move::MoveController * moveController;
            std::vector<IGameEventListener *> listeners;
        public:
            static cocos2d::Scene* createScene();
            virtual bool init();
            CREATE_FUNC(GameController);
            void registerListener(IGameEventListener * listener);
        };
    }
}

#endif // __HELLOWORLD_SCENE_H__
