#ifndef SRC_GAMECHARACTER_H
#define SRC_GAMECHARACTER_H

#include "cocos2d.h"

using cocos2d::Vec2;
using cocos2d::Sprite;
using std::string;

class GameCharacter {
 private:
  Vec2 spawn;
  Vec2 target;
  Sprite *sprite;
 public:
  GameCharacter(const Vec2 &, Sprite *, string &);
  virtual void updatePosition(const Vec2 &);
  virtual void setTarget(const Vec2 &);
  virtual Sprite *getSprite();
  virtual const Vec2 &getSpawn() const;
  virtual const Vec2 &getTarget() const;
};

#endif //SRC_GAMECHARACTER_H
