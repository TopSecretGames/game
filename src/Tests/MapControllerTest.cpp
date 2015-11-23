#include "fakeit.hpp"
#include "MapController.h"

class MyListener : public IMapEventListener {
 public:
  int numCalled;
  MyListener() : numCalled(0) {};
  virtual void onMapLoad(cocos2d::TMXTiledMap *) { ++numCalled; }
};


class Mocked:public MapController{
  virtual void loadMapFromFile(const std::string&){ }
};
using namespace fakeit;

TEST_CASE("Map controller tests", "[MapController]") {

  // cocos2d::TMXTiledMap tmm;

  Mocked mocked;
  MyListener listener;

  mocked.registerListener(&listener);
  mocked.loadMap("map1.tmx");
  REQUIRE(listener.numCalled == 1);
}
