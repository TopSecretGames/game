#include "GameLoopLayer.h"

namespace tsg{
  GameLoopLayer::GameLoopLayer(){
    onUpdate = [](float){};
  }
  GameLoopLayer::GameLoopLayer(std::function<void(float)> onUpdate):onUpdate(onUpdate){}

  void GameLoopLayer::update(float time){
    onUpdate(time);
  }

}
