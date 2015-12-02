#include "EffectsController.h"

#include <base/ccMacros.h>

namespace tsg {
namespace effect {
EffectsController::EffectsController(){};

void EffectsController::addEffect(std::unique_ptr<IBaseEffect> effect) {
  CCASSERT(effects.find(effect->getName()) == effects.end(), "effect is already added");
  effects[effect->getName()] = std::move(effect);
}

void EffectsController::onInit(){};

void EffectsController::onUpdate(float delta) {
  for (auto it = effects.begin(); it != effects.end();) {
    it->second->update(delta);
    if (it->second->isFinished()) {
      effects.erase(it++);
    } else {
      ++it;
    }
  }
}

}
}
