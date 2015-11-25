#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do
                           // this in one cpp file

#include "GameController.h"
#include "IGameEventListener.h"

#include "fakeit.hpp"

using namespace fakeit;

TEST_CASE("Tests that game event listeners got notified well",
          "[GameController]") {
  Mock<tsg::game::IGameEventListener> listenerMock;
  When(Method(listenerMock, onInit)).Return();
  tsg::game::GameController controller;
  controller.registerListener(&listenerMock.get());
  Verify(Method(listenerMock, onInit)).Exactly(0);
  controller.init();
  Verify(Method(listenerMock, onInit)).Exactly(1);
}