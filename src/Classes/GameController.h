#ifndef __GAMECONTROLLER_H__
#define __GAMECONTROLLER_H__

#include "MapController.h"
#include "MoveController.h"
#include "IGameEventListener.h"

#include "cocos2d.h"

namespace tsg {
namespace game {
/*
 Manages game components
 */
class GameController : public cocos2d::Layer {
 private:
  GameController();
  GameController(const GameController &);
  GameController &operator=(GameController &);

  static GameController *p_instance;
  map::MapController *mapController;
  move::MoveController *moveController;
  std::vector<IGameEventListener *> listeners;

 public:
  static GameController *getInstance() {
    if (!p_instance) {
      p_instance = new GameController();
    }
    return p_instance;
  }
  static cocos2d::Scene *createScene();
  bool init() override;
  void update(float) override;
  void injectControllers();
  void injectControllers(move::MoveController *moveController,
                         map::MapController *mapController);

  map::MapController *getMapController();
  move::MoveController *getMoveController();
  void registerListener(IGameEventListener *listener);
};
}
}

#endif  // __HELLOWORLD_SCENE_H__
