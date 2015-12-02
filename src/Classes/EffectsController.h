#ifndef EFFECTS_CONTROLLER_H
#define EFFECTS_CONTROLLER_H

#include "IBaseEffect.h"
#include "IGameEventListener.h"

#include <map>

namespace tsg {
namespace effect {
class EffectsController: public game::IGameEventListener {
 private:
  std::map<std::string, std::unique_ptr<IBaseEffect>> effects;

 protected:
  virtual void onUpdate(float) override;
  virtual void onInit() override;

 public:
  EffectsController();
  void addEffect(std::unique_ptr<IBaseEffect>);
};
}
}

#endif
