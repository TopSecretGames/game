#ifndef __MOVECONTROLLER_H__
#define __MOVECONTROLLER_H__

#include "IMapEventListener.h"
#include "IGameEventListener.h"
#include "GameCharacter.h"
#include "ILobbyEventListener.h"

#include "TMXPathFinding.h"
#include "cocos2d.h"

namespace tsg {
namespace move {

using cocos2d::Vec2;
using cocos2d::TMXTiledMap;
using cocos2d::Sprite;
using cocos2d::TMXObjectGroup;
using cocos2d::Size;

using std::string;
/*
 Holds objects positioning and guarantees that
 their position will be valid to each other.

 Provides API to control objects position.
 */
class MoveController:
    public map::IMapEventListener,
    public game::IGameEventListener,
    public lobby::ILobbyEventListener {
 protected:
  TMXTiledMap *map;
  std::map<string, GameCharacter *> characters;
  TMXPathFinding *pathFinding;
  std::vector<int> roadTiles;

  virtual Size calcTileSize() const;
  virtual TMXObjectGroup *findSpawnObject(const string &) const;
  virtual Vec2 findPlayerSpawn() const;
  void respawnCharacter(string &name);
  virtual Sprite *initSprite() const;
  virtual Sprite *findWaterTile(const Vec2) const;
  void registerSceneUpdateCallback();
  void cleanupPathFindingFlags() const;
  void initPathFinding();
  Vec2 convertNodeToGridPosition(const Vec2 &) const;
  virtual Vec2 findObjectNodePosition(const string &, const string &) const;
  virtual Vec2 findObjectGridPosition(const string &, const string &) const;

  void onMapLoad(TMXTiledMap *) override;
  void onInit() override;
  virtual void onUpdate(float);
 public:
  virtual void onStartGame() override;
  void onViewCoordinatesChange(Vec2) override;
  void onNightTime() override;
  void onDayTime() override;
  void onGameHourPass() override;
};
}
}
#endif /* __MOVECONTROLLER_H__ */
