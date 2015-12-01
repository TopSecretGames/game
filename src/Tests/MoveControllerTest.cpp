#include "GameController.h"
#include "MapController.h"
#include "MoveController.h"
#include "EffectsController.h"

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

  auto spawnPoint = cocos2d::Vec2(1.0f, 2.0f);
  Mock<MapControllerMock> mapControllerMock;
  When(OverloadedMethod(mapControllerMock, lookAt, void(cocos2d::Vec2)))
      .Return();
  ExposedController controller;
  auto gameController = tsg::game::GameController::getInstance();
  tsg::effect::EffectsController effectsController;
  gameController->injectControllers(&controller, &mapControllerMock.get(), &effectsController);
  controller.onMapLoad(&map);
  REQUIRE(controller.getPlayerSpawn() == spawnPoint);
  REQUIRE(controller.getPlayerPosition() == controller.getPlayerSpawn());
  Verify(OverloadedMethod(mapControllerMock, lookAt, void(cocos2d::Vec2))
             .Using(spawnPoint))
      .Once();
}
