#include "GameController.h"
#include <iostream>

void tsg::game::GameController::createScene() {
  auto controller = tsg::game::GameController::getInstance();
  controller->init();
}

void tsg::game::GameController::registerListener(IGameEventListener *listener) {
  this->listeners.push_back(listener);
}

void tsg::game::GameController::injectControllers() {
  injectControllers(
          new move::MoveController(), 
          new map::MapController(), 
          new effect::EffectsController(),
          lobby::LobbyController::create()
  );
}

void tsg::game::GameController::injectControllers(
    move::MoveController *moveController,
    map::MapController *mapController,
    effect::EffectsController *effectsController,
    lobby::LobbyController *lobbyController
) {
  CCLOG("initializing controllers");
  this->mapController = mapController;
  this->moveController = moveController;
  this->effectsController = effectsController;
  this->lobbyController = lobbyController;
  CCLOG("controllers initialized");
}

bool tsg::game::GameController::init() {
  this->scene = cocos2d::Scene::create();
  this->scene->addChild(this);
  this->injectControllers();
  
  if (!cocos2d::Layer::init()) {
    return false;
  }
  if (mapController) {
    registerListener(mapController);
  }
  if (moveController) {
    registerListener(moveController);
  }
  if (lobbyController) {
    registerListener(lobbyController);
    lobbyController->registerListener(this);
  }
  for_each(listeners.begin(), listeners.end(),
           [](IGameEventListener *l) { l->onInit(); });
  scheduleUpdate();
  return true;
}

void tsg::game::GameController::onStartGame() {
    cocos2d::Director::getInstance()->pushScene(this->scene);
    mapController->loadMap("data/map1.tmx");
}

void tsg::game::GameController::update(float delta) {
  std::cout << "upd\n";
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

tsg::lobby::LobbyController *tsg::game::GameController::getLobbyController() {
  return this->lobbyController;
}

tsg::game::GameController *tsg::game::GameController::instance = 0;

tsg::game::GameController::GameController() { }
