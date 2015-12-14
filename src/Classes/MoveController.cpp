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
  auto sprite = initSprite();
  auto spawn = findPlayerSpawn();
  string name = "player";
  auto gc = new GameCharacter(spawn, sprite, name);
  characters[name] = gc;
  respawnCharacter(name);
  initPathFinding();
  registerSceneUpdateCallback();
}
void MoveController::initPathFinding() {
  pathFinding = new TMXPathFinding(map, TMXPathFinding::FOUR);
  pathFinding->setTileLayers({"road"});
  for (int i = 0; i < 128; ++i) {
    for (int j = 0; j < 128; ++j) {
      auto g = map->getLayer("road")->getTileGIDAt(Vec2(i, j));
      if (!g) {
        continue;
      }
      roadTiles.push_back(g);
    }
  }
}
void MoveController::registerSceneUpdateCallback() {
  auto gameLayer = new GameLoopLayer([&](float dt) { this->onUpdate(dt); });
  gameLayer->scheduleUpdate();
  gameLayer->init();
  map->addChild(gameLayer);
}

void MoveController::onUpdate(float delta) {
  std::cout << "delta " << delta << std::endl;
}

TMXObjectGroup *MoveController::findSpawnObject(const string &layer) const {
  auto objectGroup = map->getObjectGroup(layer);
  assert(objectGroup != nullptr);
  return objectGroup;
}

void MoveController::respawnCharacter(string &name) {
  auto gc = characters[name];
  auto sprite = gc->getSprite();
  sprite->setPosition(gc->getSpawn());
  //todo calc Z correctly
  sprite->setLocalZOrder(2);
  auto gameController = game::GameController::getInstance();
  gameController->getMapController()->lookAt(sprite->getPosition());
//  gameController->getMapController()->lookAt(findWaterTile(Vec2(0, 0))->getPosition());
}

Sprite *MoveController::initSprite() const {

  auto sprite = Sprite::create();
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
  map->addChild(sprite);
  return sprite;
}

Vec2 MoveController::convertNodeToGridPosition(const Vec2 &v) const {
  auto point = CC_POINT_POINTS_TO_PIXELS(v);
  auto x0y0 = CC_POINT_POINTS_TO_PIXELS(findWaterTile(Vec2(0, 0))->getPosition());
  float offsetX = (point.x - x0y0.x) / map->getTileSize().width;
  float offsetY = (x0y0.y - point.y) / map->getTileSize().height;
  return Vec2(
      static_cast<int>(ceilf(offsetX + offsetY)),
      static_cast<int>(ceilf(offsetY - offsetX) + 1)
  );
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

Vec2 MoveController::findObjectNodePosition(const string &layer, const string &name) const {
  return findWaterTile(findObjectGridPosition(layer, name))->getPosition();
}

Vec2 MoveController::findPlayerSpawn() const {
  return findObjectNodePosition("spawn point", "spawn1");
}

Sprite *MoveController::findWaterTile(const Vec2 v) const {
  return map->getLayer("water")->getTileAt(v);
}

void MoveController::onStartGame() {
  auto listener = cocos2d::EventListenerTouchOneByOne::create();
  listener->onTouchBegan = [&](cocos2d::Touch *touch, cocos2d::Event *) {
    auto player = characters["player"];
    player->setTarget(map->convertTouchToNodeSpace(touch));
    std::cout << "target set to " << player->getTarget().x << "," << player->getTarget().y << std::endl;
    cleanupPathFindingFlags();
    std::vector<Vec2> path = pathFinding->getPathUsingWalkable(
        convertNodeToGridPosition(player->getSprite()->getPosition()),
        convertNodeToGridPosition(player->getTarget()),
        roadTiles
    );
    std::vector<string> flags = {
        "data/green-flag.png",
        "data/red-flag.png",
        "data/blue-flag.png",
        "data/silver-flag.png",
        "data/pink-flag.png",
    };
    int i = 0;
    for (auto p : path) {
      auto item = findWaterTile(p)->getPosition();
      auto sprite = Sprite::create(flags[i % flags.size()]);
      sprite->setName("path_finding_flag_" + std::to_string(i));
      i++;
      map->addChild(sprite);
      auto s = Vec2(sprite->getContentSize().width, sprite->getContentSize().height);
      sprite->setPosition(item + s);
      sprite->setLocalZOrder(100);
    }
    return true;
  };
  cocos2d::Director::getInstance()
      ->getEventDispatcher()
      ->addEventListenerWithFixedPriority(listener, 30);
}

void MoveController::cleanupPathFindingFlags() const {
  auto existTargetFlag = map->getChildByName("target_flag");
  if (existTargetFlag != nullptr) {
    map->removeChild(existTargetFlag, true);
  }
  for (int i = 0; ; ++i) {
    auto child = map->getChildByName("path_finding_flag_" + std::to_string(i));
    if (child != nullptr) {
      map->removeChild(child, true);
    } else {
      break;
    }
  }
}

void MoveController::onInit() {
}

void MoveController::onViewCoordinatesChange(cocos2d::Vec2) { };
void MoveController::onNightTime() { };
void MoveController::onDayTime() { };
void MoveController::onGameHourPass() { };

}

}
