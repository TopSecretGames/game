#include "MoveController.h"

namespace tsg {
    namespace move {
        void MoveController::onMapLoad(cocos2d::TMXTiledMap * map) {
            this->map = map;
        }
    }    
}
