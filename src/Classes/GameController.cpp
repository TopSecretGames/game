#include "GameController.h"

#include <algorithm>

cocos2d::Scene *tsg::game::GameController::createScene() {
  auto scene = cocos2d::Scene::create();
  auto controller = tsg::game::GameController::getInstance();
  scene->addChild(controller);
  controller->injectControllers();
  controller->init();
  return scene;
}

void tsg::game::GameController::registerListener(IGameEventListener *listener) {
  this->listeners.push_back(listener);
}

void tsg::game::GameController::injectControllers() {
  injectControllers(new move::MoveController(), new map::MapController(this));
}

void tsg::game::GameController::injectControllers(
    move::MoveController *moveController, map::MapController *mapController) {
  CCLOG("initializing controllers");
  this->mapController = mapController;
  this->moveController = moveController;
  CCLOG("controllers initialized");
}

bool tsg::game::GameController::init() {
  if (!Layer::init()) {
    return false;
  }
  registerListener(mapController);
  for_each(listeners.begin(), listeners.end(),
           [](IGameEventListener *l) { l->onInit(); });
  mapController->loadMap("data/map1.tmx");
  scheduleUpdate();
  return true;
}

void tsg::game::GameController::update(float delta) {
  for_each(listeners.begin(), listeners.end(),
           [delta](IGameEventListener *l) { l->onUpdate(delta); });
}

tsg::map::MapController *tsg::game::GameController::getMapController() {
  return this->mapController;
}

tsg::move::MoveController *tsg::game::GameController::getMoveController() {
  return this->moveController;
}

tsg::game::GameController *tsg::game::GameController::p_instance = 0;

tsg::game::GameController::GameController() {}
