#include "MoveController.h"
#include "GameController.h"
#include "MapController.h"

#include "fakeit.hpp"

using namespace fakeit;

class ExposedController : public tsg::move::MoveController {
 public:
  virtual cocos2d::Vec2 getPlayerSpawn() const;
  virtual cocos2d::Vec2 getPlayerPosition() const;
};

class MapControllerMock : public tsg::map::MapController {
  virtual void loadMapFromFile(const std::string &) {}
  //  virtual void initTouchEvents() {}
 public:
  MapControllerMock() : MapController(nullptr) {}
};

cocos2d::Vec2 ExposedController::getPlayerSpawn() const { return playerSpawn; }
cocos2d::Vec2 ExposedController::getPlayerPosition() const {
  return playerPosiiton;
}

TEST_CASE("That player spawns well in spawn point and map is scrolled to it",
          "[MoveController]") {
  cocos2d::Vector<cocos2d::TMXObjectGroup *> groups;
  cocos2d::TMXObjectGroup group;
  group.setGroupName("spawn point");
  cocos2d::ValueVector v;
  cocos2d::ValueMap vp;
  vp["name"] = "spawn1";
  vp["x"] = cocos2d::Value(1.0f);
  vp["y"] = cocos2d::Value(2.0f);
  v.push_back(cocos2d::Value(vp));
  group.setObjects(v);
  groups.pushBack(&group);
  cocos2d::TMXTiledMap map;
  map.setObjectGroups(groups);

  Mock<MapControllerMock> mapControllerMock;
  When(Method(mapControllerMock, lookAt)).Return();
  ExposedController controller;
  auto gameController = tsg::game::GameController::getInstance();
  gameController->injectControllers(&controller, &mapControllerMock.get());
  controller.onMapLoad(&map);
  auto spawnPoint = cocos2d::Vec2(1.0f, 2.0f);
  REQUIRE(controller.getPlayerSpawn() == spawnPoint);
  REQUIRE(controller.getPlayerPosition() == controller.getPlayerSpawn());
  Verify(Method(mapControllerMock, lookAt).Using(spawnPoint)).Once();
}
