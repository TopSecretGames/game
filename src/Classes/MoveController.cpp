#include "MoveController.h"

namespace move {
    void MoveController::onMapLoad(cocos2d::TMXTiledMap * map) {
        this->map = map;
    }
}
