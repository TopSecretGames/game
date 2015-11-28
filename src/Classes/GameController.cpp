#include "GameController.h"
#include "MapController.h"
#include "MoveController.h"
#include <algorithm>

tsg::game::GameController *instantiate() {
  tsg::game::GameController *pRet =
      new (std::nothrow) tsg::game::GameController();
  if (pRet) {
    pRet->injectControllers();
    if (pRet->init()) {
      pRet->autorelease();
      return pRet;
    }
  }
  delete pRet;
  pRet = nullptr;
  return nullptr;
};

cocos2d::Scene *tsg::game::GameController::createScene() {
  auto scene = cocos2d::Scene::create();
  auto controller = instantiate();
  scene->addChild(controller);
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
