#ifndef __GAMECONTROLLER_H__
#define __GAMECONTROLLER_H__

#include "MapController.h"
#include "MoveController.h"
#include "EffectsController.h"
#include "LobbyController.h"
#include "IGameEventListener.h"

#include "cocos2d.h"

namespace tsg {
namespace game {
/*
 Manages game components
 */
class GameController {
 private:
  map::MapController *mapController;
  move::MoveController *moveController;
  effect::EffectsController *effectsController;
  lobby::LobbyController *lobbyController;

  std::vector<IGameEventListener *> listeners;
  static GameController *instance;
  GameController();
  cocos2d::Scene *scene;
  
 public:
  static GameController *getInstance() {
    if (!instance) {
      instance = new GameController();
      instance->init();
    }
    return instance;
  }
  void init();
  void injectControllers();
  void injectControllers(
      move::MoveController *moveController,
      map::MapController *mapController,
      effect::EffectsController *effectsController,
      lobby::LobbyController *lobbyController
  );

  map::MapController *getMapController();
  move::MoveController *getMoveController();
  effect::EffectsController *getEffectsController();
  lobby::LobbyController *getLobbyController();
  void registerListener(IGameEventListener *listener);
};
}
}

#endif  // __HELLOWORLD_SCENE_H__
