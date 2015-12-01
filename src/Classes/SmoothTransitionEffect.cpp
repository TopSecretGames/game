#include "SmoothTransitionEffect.h"

namespace tsg {
namespace effect {
using cocos2d::Vec2;
SmoothTransitionEffect::SmoothTransitionEffect(Vec2 from, Vec2 to,
                                               float duration,
                                               cocos2d::Layer* gameLayer)
    : duration(duration),
      currentDuration(0),
      from(from),
      to(to),
      gameLayer(gameLayer) {}

void SmoothTransitionEffect::setupCoordinates(Vec2 p){
  gameLayer->setPosition(p);
}

void SmoothTransitionEffect::update(float delta) {
  currentDuration += delta;
  auto dx = from.lerp(to, currentDuration / duration);
  setupCoordinates(dx);
}

std::string SmoothTransitionEffect::getName() {
  return "smooth-transition-effect";
}

bool SmoothTransitionEffect::isFinished() {
  return currentDuration >= duration;
}
}
}
