#include "EffectsController.h"

namespace tsg {
namespace effect {
EffectsController::EffectsController(){};

void EffectsController::addEffect(std::unique_ptr<IBaseEffect> effect) {
  auto it = effects.begin();
  for(; it != effects.end(); ++it){
    if(it->first == effect->getName()) break;
  }

  if (it == effects.end()) effects.emplace(effect->getName(), std::move(effect));
}


void EffectsController::onInit(){};

void EffectsController::onUpdate(float delta) {
  for (auto it = effects.begin(); it != effects.end(); ++it) {
    it->second->update(delta);
    if (it->second->isFinished()) effects.erase(it);
  }
}

}
}
