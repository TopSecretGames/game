#ifndef SMOOTH_TRANSITION_EFFECT_H
#define SMOOTH_TRANSITION_EFFECT_H
#include "IBaseEffect.h"
#include "cocos2d.h"

namespace tsg {
namespace effect {
class SmoothTransitionEffect : public IBaseEffect {
 float duration;
 float currentDuration;
 cocos2d::Vec2 from, to;
 cocos2d::Layer* gameLayer;

 protected:
  virtual void setupCoordinates(cocos2d::Vec2);
 public:
  virtual std::string getName();
  virtual void update(float);
  virtual bool isFinished();

  SmoothTransitionEffect(cocos2d::Vec2, cocos2d::Vec2, float, cocos2d::Layer*);

};
}
}

#endif
