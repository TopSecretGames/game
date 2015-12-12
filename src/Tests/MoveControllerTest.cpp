#include "GameController.h"
#include "MoveControllerStub.h"
#include "MapController.h"

#include <assert.h>

#include "fakeit.hpp"

using cocos2d::Vec2;
using cocos2d::TMXTiledMap;
using cocos2d::TMXLayer;
using cocos2d::Size;
using cocos2d::Sprite;
using cocos2d::TMXObjectGroup;
using cocos2d::ValueVector;
using cocos2d::ValueMap;
using cocos2d::Value;

using std::string;


class MapControllerStub: public tsg::map::MapController {
 private:
  std::map<const Vec2, int> lookAtCalls;
 public:
  int lookAtTimes(const Vec2) const;
  virtual void lookAt(Vec2) override;
  virtual void loadMapFromFile(const string &) { }
};

//=============================8<==================================

int MapControllerStub::lookAtTimes(const Vec2 v) const{
  auto it = lookAtCalls.find(v);
  assert (it != lookAtCalls.end());
  return lookAtCalls.find(v)->second;
}

void MapControllerStub::lookAt(Vec2 v) {
  auto it = lookAtCalls.find(v);
  if (it != lookAtCalls.end()) {
    lookAtCalls[v] = it->second + 1;
  } else {
    lookAtCalls[v] = 1;
  }
}

//================================8<=======================================

TMXObjectGroup mkObjectGroup(Vec2 p) {
  TMXObjectGroup group;
  ValueVector v;
  ValueMap vp;
  vp["name"] = "spawn1";
  vp["x"] = Value(p.x);
  vp["y"] = Value(p.y);
  v.push_back(Value(vp));
  group.setObjects(v);
  return group;
}

TEST_CASE("That player spawns well in spawn point and map is scrolled to spawn point correctly",
          "[MoveController]") {
  Sprite zeroPointSpriteStub;
  Sprite spawnSpriteStub;
  MapControllerStub mapControllerStub;
  MoveControllerStub moveControllerStub;
  string spawnLayer = "spawn point";
  auto gameController = tsg::game::GameController::getInstance();
  auto zeroPointGrid = Vec2(0, 0);
  auto zeroPointWorld = Vec2(1000.0f, 1000.0f);
  auto spawnPointGrid = Vec2(4, 29);
  auto spawnPointWorld = Vec2(100, 100);
  auto group = mkObjectGroup(Vec2(100, 100));
  moveControllerStub.addObjectGroup(spawnLayer, &group);
  moveControllerStub.addWaterTile(zeroPointGrid, &zeroPointSpriteStub);
  moveControllerStub.addWaterTile(spawnPointGrid, &spawnSpriteStub);

  gameController->injectControllers(&moveControllerStub, &mapControllerStub, nullptr, nullptr);
  zeroPointSpriteStub.setPosition(zeroPointWorld);
  spawnSpriteStub.setPosition(spawnPointWorld);

  moveControllerStub.onMapLoad(nullptr);
  REQUIRE(moveControllerStub.getPlayerSpawn() == spawnPointWorld);
  REQUIRE(moveControllerStub.getPlayerPosition() == moveControllerStub.getPlayerSpawn());
  REQUIRE(mapControllerStub.lookAtTimes(spawnPointWorld) == 1);
}
