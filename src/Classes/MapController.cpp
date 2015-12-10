#include <iostream>
#include "GameController.h"
#include "MapController.h"
#include "SmoothTransitionEffect.h"

#include <random>

namespace tsg {
namespace map {
using cocos2d::Vec2;
MapController::MapController( const std::string root)
    : mapsRoot(root){};

MapController::MapController()
    : mapsRoot(""){};
MapController::MapController(const MapController &)
    : mapsRoot(""), currentMap(nullptr){};

void MapController::registerListener(IMapEventListener *listener) {
  this->mapEventListeners.push_back(listener);
};

void MapController::loadMapFromFile(const std::string &map) {
  auto path = mapsRoot + map;
  this->currentMap = cocos2d::TMXTiledMap::create(path);
  gameLayer->addChild(currentMap, 1);
  cocos2d::Vec2 mapSize(currentMap->getContentSize());
  cocos2d::Vec2 viewSize(gameLayer->getContentSize());
  auto center = (viewSize / 2 - mapSize / 2);
  gameLayer->setPosition(center);
  cocos2d::Director::getInstance()->pushScene(scene);
}

void MapController::notifyListeners() {
  for (auto listener : mapEventListeners) listener->onMapLoad(this->currentMap);
}

bool MapController::onTouchBegan(cocos2d::Touch *) {
  this->touchPositionStarted = gameLayer->getPosition();
  touchActive = true;
  return true;
}

bool MapController::onTouchMoved(cocos2d::Touch *touch) {
  auto c = touch->getStartLocation();
  auto d = Vec2(touch->getLocation().x, touch->getLocation().y);
  d.subtract(c);
  auto l = d.length();
  d.normalize();
  auto position = touchPositionStarted + d * l * mapScrollSpeed;
  gameLayer->setPosition(position);
  previousTouchPosition = touch->getPreviousLocation();
  previosTime = std::chrono::system_clock::now();
  return true;
}

bool MapController::onTouchEnded(cocos2d::Touch *touch) {
  auto now = std::chrono::system_clock::now();
  std::chrono::duration<double, std::ratio<1>> duration = now - previosTime;

  currentSpeed =
      (touch->getLocation() - previousTouchPosition) / duration.count() / 1000;
  touchActive = false;
  return true;
}

void MapController::initTouchEvents() {
  static bool eventListenersInited = false;
  if (eventListenersInited) return;

  this->listener = cocos2d::EventListenerTouchOneByOne::create();
  listener->setSwallowTouches(true);

  listener->onTouchBegan = [&](cocos2d::Touch *touch, cocos2d::Event *) {
    return onTouchBegan(touch);
  };
  listener->onTouchMoved = [&](cocos2d::Touch *touch, cocos2d::Event *) {
    return onTouchMoved(touch);
  };
  listener->onTouchEnded = [&](cocos2d::Touch *touch, cocos2d::Event *) {
    return onTouchEnded(touch);
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

void MapController::onInit() {
  scene = cocos2d::Scene::create();
  gameLayer = cocos2d::Layer::create();
  gameLayer->init();
  scene->init();
  scene->addChild(gameLayer);
}

void MapController::processInertialScroll(float delta) {
  if (currentSpeed.length() < minScrollSpeed || touchActive) return;
  currentSpeed *= cocos2d::clampf(1.0f - scrollFriction * delta, 0.0, 0.99);
  auto dx = currentSpeed * delta;
  auto old = gameLayer->getPosition();
  gameLayer->setPosition(old + dx);
}

void MapController::onUpdate(float delta) {
  processInertialScroll(delta);
  processTiming(delta);
}

void MapController::lookAt(cocos2d::Vec2 position) {
  Vec2 viewSize(game::GameController::getInstance()->getContentSize());
  auto point = (viewSize / 2 - position);
  gameLayer->setPosition(point);
  for (auto listener : this->mapEventListeners) {
    listener->onViewCoordinatesChange(position);
  }
}

void MapController::lookAt(cocos2d::Vec2 position, float duration,
                           std::string ) {
  auto gc = tsg::game::GameController::getInstance();
  std::unique_ptr<effect::SmoothTransitionEffect> effect(
      new effect::SmoothTransitionEffect(gameLayer->getPosition(), position,
                                         duration, gameLayer));

  gc->getEffectsController()->addEffect(std::move(effect));
}

void MapController::setScrollFriction(float friction) {
  this->scrollFriction = friction;
}

void MapController::processTiming(float delta) {
  currentTime += delta;
  static float lastHour = 0;
  static float lastDay = 1;
  static bool nightReported = false;
  auto time =
      std::fmod(currentTime, dayTime + nightTime) / (dayTime + nightTime);
  auto hour = 1.0 / hoursPerDay;
  auto dayLasts = dayTime / (dayTime + nightTime);

  auto hourNormalized = std::fmod(time, hour) / hour;
  auto stepHour = hourNormalized - lastHour;
  auto stepDay = time - lastDay;
  lastHour = hourNormalized;
  lastDay = time;

  if (stepHour < 0)
    for (auto listener : this->mapEventListeners) listener->onGameHourPass();

  if (stepDay < 0)
    for (auto listener : this->mapEventListeners) listener->onDayTime();

  if (time > dayLasts) {
    if (!nightReported) {
      nightReported = true;
      for (auto listener : this->mapEventListeners) listener->onNightTime();
    }
  } else {
    nightReported = false;
  }
}
}
}
