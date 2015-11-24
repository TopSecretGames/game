#include "fakeit.hpp"
#include "GameController.h"
#include "IGameEventListener.h"

using namespace fakeit;

TEST_CASE("Game controller tests", "[GameController]") {
    Mock<tsg::game::IGameEventListener> listenerMock;
    When(Method(listenerMock,onInit)).Return();
    tsg::game::GameController controller;
    controller.registerListener(&listenerMock.get());
    Verify(Method(listenerMock, onInit)).Exactly(0);
    controller.init();
    Verify(Method(listenerMock, onInit)).Exactly(1);
}
