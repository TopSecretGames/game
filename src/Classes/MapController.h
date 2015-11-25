#ifndef MAP_CONTROLLER_H
#define MAP_CONTROLLER_H
#include <string>
#include <tuple>
#include <vector>

#include "IMapEventListener.h"
namespace tsg {
namespace map {
class MapController {
  const float mapScrollSpeed =1.2;
  std::string mapsRoot;
  std::vector<IMapEventListener *> mapEventListeners;
  cocos2d::TMXTiledMap *currentMap;
  cocos2d::EventListenerTouchOneByOne *listener;
  cocos2d::Vec2 touchPositionStarted;
  cocos2d::Layer *gameLayer;
  typedef std::tuple<std::string, std::string> MapType;
  typedef std::vector<MapType> MapCollection;
  void notifyListeners();
  void initTouchEvents();
  virtual void loadMapFromFile(const std::string &);

 protected:
 public:

  MapController(const MapController &);
  MapController(cocos2d::Layer*);
  MapController(cocos2d::Layer*, std::string);

  void loadMap(std::string);
  void registerListener(IMapEventListener *);
};
}
}
#endif
