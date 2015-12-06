#pragma once

namespace tsg {
namespace lobby {    
class ILobbyEventListener {
 public:
  virtual void onStartGame() = 0;
  virtual ~ILobbyEventListener(){};

};
}
}