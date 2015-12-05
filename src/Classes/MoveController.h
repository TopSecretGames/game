#ifndef __MOVECONTROLLER_H__
#define __MOVECONTROLLER_H__

#include "IMapEventListener.h"
#include "cocos2d.h"
#include "IGameEventListener.h"

namespace tsg {
namespace move {

using cocos2d::Vec2;
using cocos2d::TMXTiledMap;
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
  virtual Vec2 findPlayerSpawn() const;
  virtual void respawnPlayer();
  virtual void initSprite(Vec2);
  virtual Vec2 findObjectWorldPosition(const std::string&, const std::string&) const;
  virtual Vec2 findObjectGridPosition(const std::string&, const std::string&) const;
  virtual void onMapLoad(TMXTiledMap *) override;
  virtual void onUpdate(float) override;
  virtual void onInit() override;
  virtual void onViewCoordinatesChanged(Vec2) override;
 public:
};
}
}
#endif /* __MOVECONTROLLER_H__ */
