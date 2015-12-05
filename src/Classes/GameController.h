#ifndef __GAMECONTROLLER_H__
#define __GAMECONTROLLER_H__

#include "MapController.h"
#include "MoveController.h"
#include "EffectsController.h"
#include "IGameEventListener.h"

#include "cocos2d.h"

namespace tsg {
namespace game {
/*
 Manages game components
 */
class GameController: public cocos2d::Layer {
 private:
  map::MapController *mapController;
  move::MoveController *moveController;
  effect::EffectsController *effectsController;

  std::vector<IGameEventListener *> listeners;
  static GameController *instance;
  GameController();

 public:
  static GameController *getInstance() {
    if (!instance) {
      instance = new GameController();
    }
    return instance;
  }
  static cocos2d::Scene *createScene();
  bool init() override;
  void update(float) override;
  void injectControllers();
  void injectControllers(
      move::MoveController *moveController,
      map::MapController *mapController,
      effect::EffectsController *effectsController
  );

  map::MapController *getMapController();
  move::MoveController *getMoveController();
  effect::EffectsController *getEffectsController();
  void registerListener(IGameEventListener *listener);
};
}
}

#endif  // __HELLOWORLD_SCENE_H__
