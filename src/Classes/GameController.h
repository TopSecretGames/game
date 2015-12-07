#ifndef __GAMECONTROLLER_H__
#define __GAMECONTROLLER_H__

#include "MapController.h"
#include "MoveController.h"
#include "EffectsController.h"
#include "LobbyController.h"
#include "IGameEventListener.h"
#include "ILobbyEventListener.h"

#include "cocos2d.h"

namespace tsg {
namespace game {
/*
 Manages game components
 */
class GameController: public cocos2d::Layer, lobby::ILobbyEventListener {
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
    }
    return instance;
  }
  void onStartGame();
  static void createScene();
  bool init() override;
  void update(float) override;
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
