#ifndef SRC_MOVECONTROLLERSTUB_H
#define SRC_MOVECONTROLLERSTUB_H

#include "MoveController.h"

using cocos2d::Vec2;
using cocos2d::TMXTiledMap;
using cocos2d::TMXLayer;
using cocos2d::Size;
using cocos2d::Sprite;
using cocos2d::TMXObjectGroup;
using cocos2d::ValueVector;
using cocos2d::ValueMap;
using cocos2d::Value;

using std::string;

class MoveControllerStub: public tsg::move::MoveController {
 private:
  std::map<string, TMXObjectGroup *> objectGroups;
  std::map<const Vec2, Sprite *> waterTiles;
  bool initialized;

 public:
  Vec2 getPlayerSpawn() const;
  Vec2 getPlayerPosition() const;
  Sprite *initSprite() const override;
  bool isInitialized() const;
  Sprite *findWaterTile(const Vec2) const override;
  Size calcTileSize() const override;
  TMXObjectGroup *findSpawnObject(const string &layer) const override;
  void onMapLoad(TMXTiledMap *) override;
  void onInit() override;
  void initPathFinding() override;
  void registerSceneUpdateCallback() override;
  void addObjectGroup(string, TMXObjectGroup *);
  void addWaterTile(const Vec2, Sprite *);
};

#endif //SRC_MOVECONTROLLERSTUB_H
