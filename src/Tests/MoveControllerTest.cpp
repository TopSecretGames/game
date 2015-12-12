#include "MoveController.h"
#include "GameController.h"

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

class MoveControllerStub: public tsg::move::MoveController {
 private:
  std::map<string, TMXObjectGroup *> objectGroups;
  std::map<const Vec2, Sprite *> waterTiles;
 public:
  virtual Sprite *findWaterTile(const Vec2) const override;
  virtual Size calcTileSize() const override;
  virtual Vec2 getPlayerSpawn() const;
  virtual Vec2 getPlayerPosition() const;
  virtual TMXObjectGroup *findSpawnObject(const string &layer) const override;
  virtual void initSprite(Vec2) override;
  virtual void onMapLoad(TMXTiledMap *) override;
  virtual void onInit() override;
  void addObjectGroup(string, TMXObjectGroup *);
  void addWaterTile(const Vec2, Sprite *);
};

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

Sprite *MoveControllerStub::findWaterTile(const Vec2 v) const { return waterTiles.find(v)->second; }
void MoveControllerStub::addWaterTile(const Vec2 v, Sprite *s) { waterTiles[v] = s; }
void MoveControllerStub::initSprite(Vec2) { /*stubbed*/}
void MoveControllerStub::onMapLoad(TMXTiledMap *map) { tsg::move::MoveController::onMapLoad(map); }
void MoveControllerStub::onInit() { tsg::move::MoveController::onInit(); }
Vec2 MoveControllerStub::getPlayerSpawn() const { return playerSpawn; }
Vec2 MoveControllerStub::getPlayerPosition() const { return playerPosition; }
Size MoveControllerStub::calcTileSize() const { return Size(64, 32); }
TMXObjectGroup *MoveControllerStub::findSpawnObject(const string &name) const { return objectGroups.find(name)->second; }
void MoveControllerStub::addObjectGroup(string name, TMXObjectGroup *o) { objectGroups[name] = o; }

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
