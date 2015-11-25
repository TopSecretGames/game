#include "MoveController.h"

namespace tsg {
namespace move {
void MoveController::onMapLoad(cocos2d::TMXTiledMap* map) {
  this->map = map;
  playerSpawn = findPlayerSpawn();
}

cocos2d::Vec2 MoveController::findPlayerSpawn() const {
  auto objectGroup = map->getObjectGroup("spawn point");
  assert(objectGroup != nullptr);
  auto sp = objectGroup->getObject("spawn1");
  auto point = cocos2d::Vec2(sp["x"].asFloat(), sp["y"].asFloat());
  assert(point != cocos2d::Vec2::ZERO);
  return point;
}
}
}
