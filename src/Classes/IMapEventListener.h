#ifndef MAP_EVENT_LISTENER_H
#define MAP_EVENT_LISTENER_H

#include "cocos2d.h"

namespace tsg {
namespace map {
class IMapEventListener {
 public:
  virtual void onMapLoad(cocos2d::TMXTiledMap*) = 0;
  virtual ~IMapEventListener(){};
};
}
}

#endif
