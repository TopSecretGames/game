#ifndef __MOVECONTROLLER_H__
#define __MOVECONTROLLER_H__

#include "IMapEventListener.h"
#include "cocos2d.h"
#include "IGameEventListener.h"

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
    public game::IGameEventListener {
 protected:
  TMXTiledMap *map;
  Vec2 playerSpawn;
  Vec2 playerPosition;
  virtual Size calcTileSize() const;
  virtual TMXObjectGroup *findSpawnObject(const string &) const;
  virtual Vec2 findPlayerSpawn() const;
  void respawnPlayer();
  virtual void initSprite(Vec2);
  virtual Sprite *findWaterTile(const Vec2) const;
  virtual Vec2 findObjectWorldPosition(const string &, const string &) const;
  virtual Vec2 findObjectGridPosition(const string &, const string &) const;

  void onMapLoad(TMXTiledMap *) override;
  void onInit() override;
  void onViewCoordinatesChange(Vec2) override;
  void onNightTime() override;
  void onDayTime() override;
  void onGameHourPass() override;
 public:
};
}
}
#endif /* __MOVECONTROLLER_H__ */
