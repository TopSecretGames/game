#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "MoveController.h"
#include "fakeit.hpp"

TEST_CASE( "Move controller tests", "[moveController]" ) {
//	fakeit::Mock<cocos2d::TMXTiledMap> mock;

   // Setup mock behavior.
   //fakeit::When(Method(mock,foo)).Return(1); // Method mock.foo will return 1 once.

   // Fetch the mock instance.
   //SomeInterface &i = mock.get();

   // Will print "1". 
   // std::cout << i.foo(0) << std::endl;
	
	MoveController controller;
    auto map = cocos2d::TMXTiledMap::create("../Resources/data/map1.tmx");
    //REQUIRE( controller.findPlayerPoint() == cocos2d::Vec2(0,0) );
}
