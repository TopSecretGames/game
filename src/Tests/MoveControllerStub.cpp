#include "MoveControllerStub.h"

Sprite *MoveControllerStub::findWaterTile(const Vec2 v) const { return waterTiles.find(v)->second; }
void MoveControllerStub::addWaterTile(const Vec2 v, Sprite *s) { waterTiles[v] = s; }
void MoveControllerStub::onMapLoad(TMXTiledMap *map) { tsg::move::MoveController::onMapLoad(map); }

void MoveControllerStub::onInit() {
  tsg::move::MoveController::onInit();
  initialized = true;
}

Vec2 MoveControllerStub::getPlayerSpawn() const { return characters.find("player")->second->getSpawn(); }
Vec2 MoveControllerStub::getPlayerPosition() const { return characters.find("player")->second->getSprite()->getPosition(); }
Size MoveControllerStub::calcTileSize() const { return Size(64, 32); }
TMXObjectGroup *MoveControllerStub::findSpawnObject(const string &name) const { return objectGroups.find(name)->second; }
void MoveControllerStub::addObjectGroup(string name, TMXObjectGroup *o) { objectGroups[name] = o; }
bool MoveControllerStub::isInitialized() const { return initialized; }
Sprite *MoveControllerStub::initSprite() const { return new cocos2d::Sprite(); }
void MoveControllerStub::initPathFinding() {/*stubbed TMX stuff*/}
void MoveControllerStub::registerSceneUpdateCallback() {/*stubbed TMX stuff*/}
