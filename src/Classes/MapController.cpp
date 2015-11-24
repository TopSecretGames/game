#include "MapController.h"
#include <iostream>

namespace tsg {
namespace map {
using cocos2d::Vec2;
MapController::MapController(cocos2d::Layer *layer, const std::string root)
    : mapsRoot(root), gameLayer(layer) {};

MapController::MapController(cocos2d::Layer *layer)
    : mapsRoot("data/"), gameLayer(layer) {};
MapController::MapController(const MapController &)
    : mapsRoot(""), currentMap(nullptr) {};

void MapController::registerListener(IMapEventListener *listener) {
  this->mapEventListeners.push_back(listener);
};

void MapController::loadMapFromFile(const std::string &map) {
  auto path = mapsRoot + map;
  this->currentMap = cocos2d::TMXTiledMap::create(path);
}

void MapController::notifyListeners() {
  for (auto listener : mapEventListeners) listener->onMapLoad(this->currentMap);
}

void MapController::initTouchEvents() {
  static bool eventListenersInited = false;
  if (eventListenersInited) return;

  this->listener = cocos2d::EventListenerTouchOneByOne::create();
  this->listener->onTouchBegan = [&](cocos2d::Touch *touch,
                                     cocos2d::Event *event) {
    this->touchPositionStarted = gameLayer->getPosition();
    return true;
  };

  listener->onTouchMoved = [&](cocos2d::Touch *touch, cocos2d::Event *event) {
    auto c = touch->getStartLocation();
    auto d = Vec2(touch->getLocation().x, touch->getLocation().y);
    d.subtract(c);
    d.normalize();
    gameLayer->setPosition(touchPositionStarted + d * 5.0);
  };
  listener->onTouchEnded = [&](cocos2d::Touch *touch,
                               cocos2d::Event *event) { return true; };
}

void MapController::loadMap(std::string map) {
  loadMapFromFile(map);
  notifyListeners();
}

MapController::MapCollection MapController::getMaps() {
  std::vector<MapType> collection;
  collection.push_back(std::make_tuple("FirstMap", "map1.tmx"));
  return collection;
}
}
}
