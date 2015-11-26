#include "MapController.h"
#include <iostream>

#include <random>

namespace tsg {
namespace map {
using cocos2d::Vec2;
MapController::MapController(cocos2d::Layer *layer, const std::string root)
    : mapsRoot(root), gameLayer(layer) {};

MapController::MapController(cocos2d::Layer *layer)
    : mapsRoot(""), gameLayer(layer) {};
MapController::MapController(const MapController &)
    : mapsRoot(""), currentMap(nullptr) {};

void MapController::registerListener(IMapEventListener *listener) {
  this->mapEventListeners.push_back(listener);
};

void MapController::loadMapFromFile(const std::string &map) {
  auto path = mapsRoot + map;
  this->currentMap = cocos2d::TMXTiledMap::create(path);
  gameLayer->addChild(currentMap, 1);
  cocos2d::Vec2 mapSize(currentMap->getContentSize());
  cocos2d::Vec2 viewSize(gameLayer->getContentSize());
  auto center =  (viewSize / 2 - mapSize / 2);
  gameLayer->setPosition(center);
}

void MapController::notifyListeners() {
  for (auto listener : mapEventListeners) listener->onMapLoad(this->currentMap);
}

void MapController::initTouchEvents() {
  static bool eventListenersInited = false;
  if (eventListenersInited) return;

  this->listener = cocos2d::EventListenerTouchOneByOne::create();
  listener->setSwallowTouches(true);
  listener->onTouchBegan = [&](cocos2d::Touch *, cocos2d::Event *) {
    this->touchPositionStarted = gameLayer->getPosition();
    return true;
  };

  listener->onTouchMoved = [&](cocos2d::Touch *touch, cocos2d::Event *) {
    auto c = touch->getStartLocation();
    auto d = Vec2(touch->getLocation().x, touch->getLocation().y);
    d.subtract(c);
    auto l = d.length();
    d.normalize();
    auto position = touchPositionStarted + d * l * mapScrollSpeed;
    gameLayer->setPosition(position);
  };
  listener->onTouchEnded = [&](cocos2d::Touch *,
                               cocos2d::Event *) { 
    return true; 
  };
  cocos2d::Director::getInstance()
      ->getEventDispatcher()
      ->addEventListenerWithFixedPriority(listener, 30);

  eventListenersInited = true;
}

void MapController::loadMap(std::string map) {
  loadMapFromFile(map);
  notifyListeners();
  initTouchEvents();
}

void MapController::onInit(){}
void MapController::onUpdate(float delta){
}
void MapController::lookAt(cocos2d::Vec2 position){
  gameLayer->setPosition(position);
}

}
}
