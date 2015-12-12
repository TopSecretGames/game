#define CATCH_CONFIG_MAIN

#include "GameController.h"
#include "MoveControllerStub.h"

#include "fakeit.hpp"

using namespace fakeit;

TEST_CASE("That game event listener got notified well", "[GameController]") {
  tsg::game::GameController *controller = tsg::game::GameController::getInstance();
  MoveControllerStub moveControllerStub;
  controller->injectControllers(&moveControllerStub, nullptr, nullptr, nullptr);
  controller->init();
  REQUIRE(moveControllerStub.isInitialized());
}
