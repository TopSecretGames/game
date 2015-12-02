#define CATCH_CONFIG_MAIN

#include "GameController.h"

#include "fakeit.hpp"

using namespace fakeit;

TEST_CASE("That game event listener got notified well", "[GameController]") {
  Mock<tsg::map::MapController> mapControllerMock;
  tsg::game::GameController *controller = tsg::game::GameController::getInstance();
  controller->injectControllers(nullptr, &mapControllerMock.get(), nullptr);
  When(Method(mapControllerMock, loadMap)).Return();
  When(Method(mapControllerMock, IGameEventListener::onInit)).Return();
  When(Method(mapControllerMock, IGameEventListener::onUpdate)).Return();
  Verify(Method(mapControllerMock, IGameEventListener::onInit)).Exactly(0);
  controller->init();
  Verify(Method(mapControllerMock, IGameEventListener::onInit)).Exactly(1);
}