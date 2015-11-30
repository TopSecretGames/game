#ifndef __MOVECONTROLLER_H__
#define __MOVECONTROLLER_H__

#include "IMapEventListener.h"
#include "cocos2d.h"

namespace tsg {
namespace move {

/*
 Holds objects positioning and guarantees that
 their position will be valid to each other.

 Provides API to control objects position.
 */
class MoveController : public map::IMapEventListener {
 protected:
  cocos2d::TMXTiledMap *map;
  cocos2d::Vec2 playerSpawn;
  cocos2d::Vec2 playerPosiiton;
  virtual cocos2d::Vec2 findPlayerSpawn() const;
  virtual void respawnPlayer();

 public:
  virtual void onMapLoad(cocos2d::TMXTiledMap *) override;
};
}
}
#endif /* __MOVECONTROLLER_H__ */
