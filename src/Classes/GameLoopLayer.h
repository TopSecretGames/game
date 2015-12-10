#ifndef LAYER_WITH_GAME_LOOP_H
#define LAYER_WITH_GAME_LOOP_H
#include <functional>
#include "cocos2d.h"

namespace tsg {
class GameLoopLayer : public cocos2d::Layer {
 public:
  GameLoopLayer();
  GameLoopLayer(std::function<void(float)>);

 private:
  virtual void update(float delta);
  std::function<void(float)> onUpdate;
};
}

#endif 
