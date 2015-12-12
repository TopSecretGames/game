#include "GameController.h"
#include <iostream>

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

void tsg::game::GameController::init() {
  this->injectControllers();
  if (mapController) {
    registerListener(mapController);
  }
  if (moveController) {
    registerListener(moveController);
  }
  if (lobbyController) {
    registerListener(lobbyController);
    lobbyController->registerListener(mapController);
  }
  for_each(listeners.begin(), listeners.end(),
           [](IGameEventListener *l) { l->onInit(); });
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
