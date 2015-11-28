#include "MapController.h"

#include "fakeit.hpp"

class MapControllerMock : public tsg::map::MapController {
  virtual void loadMapFromFile(const std::string &) {}
  //  virtual void initTouchEvents() {}
public:
  MapControllerMock() : MapController(nullptr) {}
};

using namespace fakeit;

TEST_CASE("That map listener will be notified on map load", "[MapController]") {
  Mock<tsg::map::IMapEventListener> listenerMock;
  MapControllerMock controllerMock;
  When(Method(listenerMock, onMapLoad)).Return();
  controllerMock.registerListener(&listenerMock.get());
  Verify(Method(listenerMock, onMapLoad)).Exactly(0);
  controllerMock.loadMap("test/map");
  Verify(Method(listenerMock, onMapLoad)).Exactly(1);
}
