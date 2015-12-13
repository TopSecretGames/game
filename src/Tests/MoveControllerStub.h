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
  virtual bool isInitialized() const;
  virtual Sprite *findWaterTile(const Vec2) const override;
  virtual Size calcTileSize() const override;
  virtual Vec2 getPlayerSpawn() const;
  virtual Vec2 getPlayerPosition() const;
  virtual TMXObjectGroup *findSpawnObject(const string &layer) const override;
  virtual void onMapLoad(TMXTiledMap *) override;
  virtual void onInit() override;
  void addObjectGroup(string, TMXObjectGroup *);
  void addWaterTile(const Vec2, Sprite *);
};

#endif //SRC_MOVECONTROLLERSTUB_H
