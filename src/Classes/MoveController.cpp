#include "MoveController.h"
#include "GameController.h"

#include <iostream>

namespace tsg {
namespace move {

void MoveController::onMapLoad(cocos2d::TMXTiledMap *map) {
  this->map = map;
  this->playerSpawn = findPlayerSpawn();
  respawnPlayer();

  //hack allows to use sprite for now
  //hack allows to use sprite for now
  //hack allows to use sprite for now
  auto k = cocos2d::Vec2((playerSpawn.x / (map->getTileSize().width) * 4.2f),
                         (playerSpawn.y / (map->getTileSize().height)) * 2.4f);
  auto t = map->getLayer("water")->getTileAt(k);
  assert(t != nullptr);
  auto p = t->getPosition();
  std::cout << "spawning player at " << p.x << "," << p.y << std::endl;
  initSprite(p);
}

void MoveController::respawnPlayer() {
  playerPosition = playerSpawn;
//  auto gameController = game::GameController::getInstance();
//  gameController->getMapController()->lookAt(playerSpawn);
}

void MoveController::initSprite(cocos2d::Vec2 center) {
  auto sprite = cocos2d::Sprite::create();
  sprite->setPosition(center);
  sprite->setLocalZOrder(2);

  map->addChild(sprite);

  //todo read animation from config
  cocos2d::Vector<cocos2d::SpriteFrame *> animFrames(10);
  for (int i = 0; i < 10; ++i) {
    auto frame = cocos2d::SpriteFrame::create(
        "data/characters/knight/IDLE/0.png",
        cocos2d::Rect(i * 67, 0, 67, 137),
        false,
        cocos2d::Vec2::ZERO,
        cocos2d::Size(cocos2d::Vec2(67, 137)));
    animFrames.pushBack(frame);
  }
  auto animation = cocos2d::Animation::createWithSpriteFrames(animFrames, 0.1f);
  auto animate = cocos2d::Animate::create(animation);
  auto repeatAnimate = cocos2d::RepeatForever::create(animate);
  sprite->runAction(repeatAnimate);
}

cocos2d::Vec2 MoveController::findPlayerSpawn() const {
  auto objectGroup = map->getObjectGroup("spawn point");
  assert(objectGroup != nullptr);
  auto sp = objectGroup->getObject("spawn1");
  auto point = cocos2d::Vec2(sp["x"].asFloat(), sp["y"].asFloat());
  assert(point != cocos2d::Vec2::ZERO);
  return point;
}

void MoveController::onInit() {
  game::GameController::getInstance()->getMapController()->registerListener(this);
}


void MoveController::onUpdate(float d) {

}

void MoveController::onViewCoordinatesChanged(cocos2d::Vec2){};

}
}
