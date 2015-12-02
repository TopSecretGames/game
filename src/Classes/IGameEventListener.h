#ifndef GAME_EVENT_LISTENER_H
#define GAME_EVENT_LISTENER_H

namespace tsg {
namespace game {
class IGameEventListener {
public:
  virtual void onInit() = 0;
  virtual void onUpdate(float) = 0;
  virtual ~IGameEventListener(){};
};
}
}

#endif // GAME_EVENT_LISTENER_H
