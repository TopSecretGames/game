#include "EffectsController.h"
#include "IBaseEffect.h"
#include "SmoothTransitionEffect.h"

#include "fakeit.hpp"

using tsg::effect::IBaseEffect;
using tsg::effect::EffectsController;
using tsg::effect::SmoothTransitionEffect;
using cocos2d::Vec2;
using namespace fakeit;

struct Effect : public IBaseEffect {
  static int instanceAmount;
  float duration;
  float current;
  int updateCalledAmount = 0;
  Effect(float d) : duration(d), current(0) { ++instanceAmount; }
  ~Effect() { --instanceAmount; }

  std::string getName() { return "effect"; }
  void update(float delta) {
    ++updateCalledAmount;
    current += delta;
  }

  bool isFinished() { return current >= duration; }
};

int Effect::instanceAmount = 0;

TEST_CASE("That effects controller inserts and deletes effects") {

  EffectsController controller;
  std::unique_ptr<Effect> upEffect(new Effect(1));
  REQUIRE(Effect::instanceAmount == 1);

  controller.addEffect(std::move(upEffect));
  controller.onUpdate(1);
  REQUIRE(Effect::instanceAmount == 0);
}

TEST_CASE("That effects controller plays effects correctly") {
  EffectsController controller;
  Effect *eff = new Effect(1);
  std::unique_ptr<Effect> upEffect(eff);
  REQUIRE(Effect::instanceAmount == 1);

  controller.addEffect(std::move(upEffect));
  controller.onUpdate(0.25);
  controller.onUpdate(0.25);
  REQUIRE((eff->current - 0.5) < 0.0001);
  controller.onUpdate(0.25);
  controller.onUpdate(0.25);
  REQUIRE(Effect::instanceAmount == 0);
}

class STEChild : public SmoothTransitionEffect {
 protected:
  virtual void setupCoordinates(Vec2 p) { lastCoords = p; };

 public:
  Vec2 lastCoords;

 public:
  STEChild(Vec2 f, Vec2 t, float d)
      : SmoothTransitionEffect(f, t, d, nullptr) {}
};

TEST_CASE("Test linear interpolation of SmoothTransitionEffect") {
  EffectsController controller;
  STEChild *eff = new STEChild(Vec2(1.0, 10.0), Vec2(2.0, 15.0), 1);
      std::unique_ptr<STEChild> upEffect(eff);

  controller.addEffect(std::move(upEffect));
  controller.onUpdate(0.25);
  controller.onUpdate(0.25);
  Vec2 c = eff->lastCoords;
  REQUIRE((c.x - 1.5) < 0.0001);
  REQUIRE((c.y - 12.5) < 0.0001);
}
