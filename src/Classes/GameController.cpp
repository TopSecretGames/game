#include "GameController.h"

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
  injectControllers(
          new move::MoveController(), 
          new map::MapController(), 
          new effect::EffectsController()
  );
}

void tsg::game::GameController::injectControllers(
    move::MoveController *moveController,
    map::MapController *mapController,
    effect::EffectsController *effectsController
) {
  CCLOG("initializing controllers");
  this->mapController = mapController;
  this->moveController = moveController;
  this->effectsController = effectsController;
  CCLOG("controllers initialized");
}

bool tsg::game::GameController::init() {
  if (!cocos2d::Layer::init()) {
    return false;
  }
  if (mapController) {
    registerListener(mapController);
  }
  if (moveController) {
    registerListener(moveController);
  }
  for_each(listeners.begin(), listeners.end(),
           [](IGameEventListener *l) { l->onInit(); });
  scheduleUpdate();
  //todo remove it. lobby has to start game properly
  mapController->loadMap("data/map1.tmx");
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

tsg::effect::EffectsController *tsg::game::GameController::getEffectsController() {
  return this->effectsController;
}

tsg::game::GameController *tsg::game::GameController::instance = 0;

tsg::game::GameController::GameController() { }
