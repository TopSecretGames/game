#include "MapController.h"

#include "fakeit.hpp"

class MapControllerStub: public tsg::map::MapController {
  virtual void loadMapFromFile(const std::string &) {}
  //  virtual void initTouchEvents() {}
public:
  MapControllerStub() : MapController(nullptr) {}
};

using namespace fakeit;

TEST_CASE("That map listener will be notified on map load", "[MapController]") {
//  Mock<tsg::map::IMapEventListener> listenerMock;
//  MapControllerStub mapControllerStub;
//  When(Method(listenerMock, onMapLoad)).Return();
//  mapControllerStub.registerListener(&listenerMock.get());
//  Verify(Method(listenerMock, onMapLoad)).Exactly(0);
//  mapControllerStub.loadMap("test/map");
//  Verify(Method(listenerMock, onMapLoad)).Exactly(1);
}
