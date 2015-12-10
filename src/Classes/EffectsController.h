#ifndef EFFECTS_CONTROLLER_H
#define EFFECTS_CONTROLLER_H

#include "IBaseEffect.h"
#include "IGameEventListener.h"
#include <memory>
#include <map>
#include <memory>

namespace tsg {
namespace effect {
class EffectsController: public game::IGameEventListener {
 private:
  std::map<std::string, std::unique_ptr<IBaseEffect>> effects;

 protected:
  virtual void onInit() override;
  void onUpdate(float );

 public:
  EffectsController();
  void addEffect(std::unique_ptr<IBaseEffect>);
};
}
}

#endif
