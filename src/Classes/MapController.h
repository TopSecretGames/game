#ifndef MAP_CONTROLLER_H
#define MAP_CONTROLLER_H
#include <string>
#include <tuple>
#include <vector>
#include <chrono>

#include "IMapEventListener.h"
#include "IGameEventListener.h"
namespace tsg {
namespace map {
class MapController:public tsg::game::IGameEventListener {
  const float mapScrollSpeed = 1.2;
  const float minScrollSpeed = 20.0;
  float scrollFriction = 3.0;

  cocos2d::Vec2 previousTouchPosition;
  std::chrono::time_point<std::chrono::system_clock> previosTime;
  cocos2d::Vec2 currentSpeed;
  bool touchActive = false;

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
  virtual void onInit();
  virtual void onUpdate(float);

  bool onTouchBegan(cocos2d::Touch *);
  bool onTouchMoved(cocos2d::Touch *);
  bool onTouchEnded(cocos2d::Touch *);

  void processInertialScroll(float delta);


 public:


  MapController(const MapController &);
  MapController(cocos2d::Layer*);
  MapController(cocos2d::Layer*, std::string);

  void loadMap(std::string);
  void registerListener(IMapEventListener *);
  void lookAt(cocos2d::Vec2);
  void setScrollFriction(float);
};
}
}
#endif
