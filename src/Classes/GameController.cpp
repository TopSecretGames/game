#include "GameController.h"
#include "MapController.h"
#include "MoveController.h"

#include <algorithm>

cocos2d::Scene* tsg::game::GameController::createScene() {
  // 'scene' is an autorelease object
  auto scene = cocos2d::Scene::create();

  // 'layer' is an autorelease object
  auto layer = GameController::create();

  // add layer as a child to scene
  scene->addChild(layer);

  // return the scene
  return scene;
}

void tsg::game::GameController::registerListener(IGameEventListener* listener) {
  this->listeners.push_back(listener);
}

bool tsg::game::GameController::init() {
  if (!Layer::init()) {
    return false;
  }
  CCLOG("initializing controllers");
  this->mapController = new map::MapController(dynamic_cast<cocos2d::Layer*>(this));
  this->moveController = new move::MoveController();
  CCLOG("controllers initialized");
  for_each(listeners.begin(), listeners.end(),
           [](IGameEventListener* l) { l->onInit(); });
//  mapController->loadMap("data/map1.tmx");
  return true;
}
