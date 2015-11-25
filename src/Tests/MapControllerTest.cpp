#include "MapController.h"

#include "fakeit.hpp"

class MyListener : public tsg::map::IMapEventListener {
 public:
  int numCalled;
  MyListener() : numCalled(0) {};
  virtual void onMapLoad(cocos2d::TMXTiledMap *) { ++numCalled; }
};

class Mocked : public tsg::map::MapController {
  virtual void loadMapFromFile(const std::string &) {}

 public:
  Mocked() : MapController(nullptr) {}
};

using namespace fakeit;

TEST_CASE("Map controller tests", "[MapController]") {

  Mocked mocked;
  MyListener listener;

  mocked.registerListener(&listener);
  mocked.loadMap("data/map1.tmx");
  REQUIRE(listener.numCalled == 1);
}
