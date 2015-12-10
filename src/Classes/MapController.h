#ifndef MAP_CONTROLLER_H
#define MAP_CONTROLLER_H
#include <chrono>
#include <string>
#include <tuple>
#include <vector>

#include "IGameEventListener.h"
#include "IMapEventListener.h"
#include "GameLoopLayer.h"

namespace tsg {
namespace map {
class MapController :  public tsg::game::IGameEventListener {
  const float mapScrollSpeed = 1.2;
  const float minScrollSpeed = 20.0;
  const float dayTime = 2 * 60;  // seconds
  const float nightTime = 1 * 60;
  const float hoursPerDay = 24.0;

  float scrollFriction = 3.0;
  cocos2d::Vec2 previousTouchPosition;
  std::chrono::time_point<std::chrono::system_clock> previosTime;
  cocos2d::Vec2 currentSpeed;
  bool touchActive = false;

  std::string mapsRoot;
  std::vector<IMapEventListener *> mapEventListeners;
  cocos2d::EventListenerTouchOneByOne *listener;
  cocos2d::Vec2 touchPositionStarted;
  GameLoopLayer *gameLayer;
  cocos2d::TMXTiledMap *currentMap;
  double currentTime;
  cocos2d::Scene *scene;
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
  void processSmoothTransition(float delta);
  void processTiming(float delta);
  virtual void update(float delta);

 public:
  MapController(const MapController &);
  MapController();
  MapController(std::string);

  virtual void loadMap(std::string);
  virtual void lookAt(cocos2d::Vec2);
  virtual void lookAt(cocos2d::Vec2, float, std::string);
  void registerListener(IMapEventListener *);
  void setScrollFriction(float);
};
}
}
#endif
