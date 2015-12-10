#include "EffectsController.h"
#include "IBaseEffect.h"
#include "SmoothTransitionEffect.h"

#include "fakeit.hpp"

using tsg::effect::IBaseEffect;
using tsg::effect::EffectsController;
using tsg::effect::SmoothTransitionEffect;
using cocos2d::Vec2;
using namespace fakeit;

class EffectsControllerStub : public EffectsController {
 public:
  virtual void onUpdate(float) ;
  virtual void onInit() override;
};

class STEChild : public SmoothTransitionEffect {
 protected:
  virtual void setupCoordinates(Vec2 p) { lastCoords = p; };

 public:
  Vec2 lastCoords;

 public:
  STEChild(Vec2 f, Vec2 t, float d)
      : SmoothTransitionEffect(f, t, d, nullptr) {}
};

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

//================8<==================

void EffectsControllerStub::onInit() { tsg::effect::EffectsController::onInit();}
void EffectsControllerStub::onUpdate(float d) { tsg::effect::EffectsController::onUpdate(d);}

int Effect::instanceAmount = 0;

//================8<==================

TEST_CASE("That effects controller inserts and deletes effects") {
  EffectsControllerStub effectsControllerStub;
  std::unique_ptr<Effect> upEffect(new Effect(1));
  REQUIRE(Effect::instanceAmount == 1);

  effectsControllerStub.addEffect(std::move(upEffect));
  effectsControllerStub.onUpdate(1);
  REQUIRE(Effect::instanceAmount == 0);
}

TEST_CASE("That effects controller plays effects correctly") {
  EffectsControllerStub effectsControllerStub;
  Effect *eff = new Effect(1);
  std::unique_ptr<Effect> upEffect(eff);
  REQUIRE(Effect::instanceAmount == 1);

  effectsControllerStub.addEffect(std::move(upEffect));
  effectsControllerStub.onUpdate(0.25);
  effectsControllerStub.onUpdate(0.25);
  REQUIRE((eff->current - 0.5) < 0.0001);
  effectsControllerStub.onUpdate(0.25);
  effectsControllerStub.onUpdate(0.25);
  REQUIRE(Effect::instanceAmount == 0);
}

TEST_CASE("Test linear interpolation of SmoothTransitionEffect") {
  EffectsControllerStub effectsControllerStub;
  STEChild *eff = new STEChild(Vec2(1.0, 10.0), Vec2(2.0, 15.0), 1);
      std::unique_ptr<STEChild> upEffect(eff);

  effectsControllerStub.addEffect(std::move(upEffect));
  effectsControllerStub.onUpdate(0.25);
  effectsControllerStub.onUpdate(0.25);
  Vec2 c = eff->lastCoords;
  REQUIRE((c.x - 1.5) < 0.0001);
  REQUIRE((c.y - 12.5) < 0.0001);
}
