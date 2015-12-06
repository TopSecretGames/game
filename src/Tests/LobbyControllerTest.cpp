#include "LobbyController.h"
#include "ILobbyEventListener.h"

#include "fakeit.hpp"

using namespace fakeit;

class LobbyControllerStub: public tsg::lobby::LobbyController {
 public:
  void startGame(cocos2d::Ref* pSender);
  void registerListener(tsg::lobby::ILobbyEventListener* listener);
};

void LobbyControllerStub::startGame(cocos2d::Ref* pSender) {
    tsg::lobby::LobbyController::startGame(pSender);
};
void LobbyControllerStub::registerListener(tsg::lobby::ILobbyEventListener* listener) { 
    tsg::lobby::LobbyController::registerListener(listener); 
};

TEST_CASE("Tests that lobby event listeners got notified well",
          "[LobbyController]") {
  Mock<tsg::lobby::ILobbyEventListener> listenerMock;
  When(Method(listenerMock, onStartGame)).Return();
  LobbyControllerStub controller;
  controller.registerListener(&listenerMock.get());
  Verify(Method(listenerMock, onStartGame)).Exactly(0);
  Mock<cocos2d::Ref> ref;
  controller.startGame(&ref.get());
  Verify(Method(listenerMock, onStartGame)).Exactly(1);
}