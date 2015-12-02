#ifndef EFFECTS_CONTROLLER_H
#define EFFECTS_CONTROLLER_H

#include "IBaseEffect.h"
#include "IGameEventListener.h"

namespace tsg {
namespace effect {
class EffectsController : public game::IGameEventListener {
  std::map<std::string, std::unique_ptr<IBaseEffect>> effects;

 public:
  EffectsController();
  void addEffect(std::unique_ptr<IBaseEffect>);
  virtual void onUpdate(float delta);
  virtual void onInit();
};
}
}

#endif
