#include "MoveControllerStub.h"

Sprite *MoveControllerStub::findWaterTile(const Vec2 v) const { return waterTiles.find(v)->second; }
void MoveControllerStub::addWaterTile(const Vec2 v, Sprite *s) { waterTiles[v] = s; }
void MoveControllerStub::onMapLoad(TMXTiledMap *map) { tsg::move::MoveController::onMapLoad(map); }

void MoveControllerStub::onInit() {
  tsg::move::MoveController::onInit();
  initialized = true;
}

Vec2 MoveControllerStub::getPlayerSpawn() const { return playerSpawn; }
Vec2 MoveControllerStub::getPlayerPosition() const { return playerPosition; }
Size MoveControllerStub::calcTileSize() const { return Size(64, 32); }
TMXObjectGroup *MoveControllerStub::findSpawnObject(const string &name) const { return objectGroups.find(name)->second; }
void MoveControllerStub::addObjectGroup(string name, TMXObjectGroup *o) { objectGroups[name] = o; }
bool MoveControllerStub::isInitialized() const { return initialized; }
