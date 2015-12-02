#include "MoveController.h"
#include "GameController.h"
#include "MapController.h"

#include "fakeit.hpp"

using namespace fakeit;

class MoveControllerStub: public tsg::move::MoveController {
 public:
  virtual cocos2d::Vec2 getPlayerSpawn() const;
  virtual cocos2d::Vec2 getPlayerPosition() const;
  virtual void initSprite(cocos2d::Vec2) override;
  virtual void onMapLoad(cocos2d::TMXTiledMap *) override;
  virtual void onInit() override;
  virtual void onUpdate(float) override;
};

class MapControllerStub: public tsg::map::MapController {
  virtual void loadMapFromFile(const std::string &) { }
 public:
  MapControllerStub() : MapController(nullptr) { }
};

class TMXTiledMapStub: public cocos2d::TMXTiledMap {
 public:
  virtual cocos2d::TMXLayer *getLayer(const std::string &layerName) const override;
};

class TMXLayerStub: public cocos2d::TMXLayer {

 public:
  virtual cocos2d::Sprite *getTileAt(const cocos2d::Vec2 &tileCoordinate) override;
};

class SpriteStub: public cocos2d::Sprite {

 public:
  virtual const cocos2d::Vec2 &getPosition() const override;
};

//=============================8<==================================

void MoveControllerStub::initSprite(cocos2d::Vec2 vec2) { /*stubbed*/}
void MoveControllerStub::onMapLoad(cocos2d::TMXTiledMap *map) { tsg::move::MoveController::onMapLoad(map);}
void MoveControllerStub::onInit() { tsg::move::MoveController::onInit();}
void MoveControllerStub::onUpdate(float d) { tsg::move::MoveController::onUpdate(d);}

const cocos2d::Vec2 &SpriteStub::getPosition() const { return cocos2d::Vec2::ZERO; }
cocos2d::TMXLayer *TMXTiledMapStub::getLayer(const std::string &layerName) const { return nullptr; }
cocos2d::Sprite *TMXLayerStub::getTileAt(const cocos2d::Vec2 &tileCoordinate) { return nullptr; }
cocos2d::Vec2 MoveControllerStub::getPlayerSpawn() const { return playerSpawn; }
cocos2d::Vec2 MoveControllerStub::getPlayerPosition() const { return playerPosition; }

//================================8<=======================================

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
  TMXTiledMapStub mapStub;
  mapStub.setObjectGroups(groups);
  Mock<cocos2d::TMXTiledMap> mapMock(mapStub);
  TMXLayerStub layerStub;
  Mock<cocos2d::TMXLayer> layerMock(layerStub);
  SpriteStub spriteStub;
  Mock<cocos2d::Sprite> spriteMock(spriteStub);
  auto spawnPoint = cocos2d::Vec2(1.0f, 2.0f);
  When(ConstOverloadedMethod(spriteMock, getPosition,
           const cocos2d::Vec2&())).Return(spawnPoint);
  When(Method(layerMock, getTileAt)).Return(&spriteMock.get());
  When(Method(mapMock, getLayer)).Return(&layerMock.get());

  Mock<MapControllerStub> mapControllerMock;
  When(Method(mapControllerMock, lookAt)).Return();
  MoveControllerStub moveControllerStub;
  auto gameController = tsg::game::GameController::getInstance();
  gameController->injectControllers(&moveControllerStub, &mapControllerMock.get());
  moveControllerStub.onMapLoad(&mapStub);

  REQUIRE(moveControllerStub.getPlayerSpawn() == spawnPoint);
  REQUIRE(moveControllerStub.getPlayerPosition() == moveControllerStub.getPlayerSpawn());
  //todo enable it when fixed
//  Verify(Method(mapControllerMock, lookAt).Using(spawnPoint)).Once();
}

