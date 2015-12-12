#include "MoveController.h"
#include "GameController.h"

#include <iostream>

using cocos2d::Vec2;
using cocos2d::Vector;
using cocos2d::TMXTiledMap;
using cocos2d::Sprite;
using cocos2d::SpriteFrame;
using cocos2d::TMXObjectGroup;
using cocos2d::TMXLayer;
using cocos2d::Size;
using cocos2d::ValueVector;
using cocos2d::ValueMap;
using cocos2d::Value;

using std::string;

namespace tsg {
namespace move {

Size MoveController::calcTileSize() const {
  return map->getTileSize();
}

void MoveController::onMapLoad(TMXTiledMap *map) {
  this->map = map;
  this->playerSpawn = findPlayerSpawn();
  std::cout<<"player spawned well!!"<<std::endl;
  respawnPlayer();
  initSprite(playerSpawn);
}

TMXObjectGroup* MoveController::findSpawnObject(const string& layer) const {
  auto objectGroup = map->getObjectGroup(layer);
  assert(objectGroup != nullptr);
  return objectGroup;
}

void MoveController::respawnPlayer() {
  playerPosition = playerSpawn;
  auto gameController = game::GameController::getInstance();
  gameController->getMapController()->lookAt(playerSpawn);
}

void MoveController::initSprite(Vec2 center) {
  auto sprite = Sprite::create();
  sprite->setPosition(center);

  //todo calc Z correctly
  sprite->setLocalZOrder(2);

  map->addChild(sprite);

  //todo read animation from config
  Vector<SpriteFrame *> animFrames(10);
  for (int i = 0; i < 10; ++i) {
    auto frame = cocos2d::SpriteFrame::create(
        "data/characters/knight/IDLE/0.png",
        cocos2d::Rect(i * 67, 0, 67, 137),
        false,
        Vec2::ZERO,
        Size(Vec2(67, 137)));
    animFrames.pushBack(frame);
  }
  auto animation = cocos2d::Animation::createWithSpriteFrames(animFrames, 0.1f);
  auto animate = cocos2d::Animate::create(animation);
  auto repeatAnimate = cocos2d::RepeatForever::create(animate);

  sprite->runAction(repeatAnimate);
}

Vec2 MoveController::findObjectGridPosition(const string &layer, const string &name) const {
  auto objectGroup = findSpawnObject(layer);
  auto sp = objectGroup->getObject(name);
  auto point = Vec2(sp["x"].asFloat(), sp["y"].asFloat());
  assert(point != Vec2::ZERO);
  auto tileSize = calcTileSize();
  auto x0y0 = findWaterTile(Vec2(0, 0))->getPosition();
  auto translatedPoint = Vec2(point.x, x0y0.y - point.y);
  auto pointToPixels = CC_POINT_POINTS_TO_PIXELS(translatedPoint);
  auto ratio = tileSize.width / tileSize.height;
  return Vec2(ceilf(pointToPixels.x / tileSize.width * ratio), ceilf(pointToPixels.y / tileSize.height));
}

Vec2 MoveController::findObjectWorldPosition(const string &layer, const string &name) const {
  return findWaterTile(findObjectGridPosition(layer, name))->getPosition();
}

Vec2 MoveController::findPlayerSpawn() const {
  return findObjectWorldPosition("spawn point", "spawn1");
}

Sprite *MoveController::findWaterTile(const Vec2 v) const {
  return map->getLayer("water")->getTileAt(v);
}

void MoveController::onInit() {

}

void MoveController::onViewCoordinatesChange(cocos2d::Vec2) { };
void MoveController::onNightTime(){};
void MoveController::onDayTime(){};
void MoveController::onGameHourPass(){};

}

}
