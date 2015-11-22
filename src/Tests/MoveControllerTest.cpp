#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "MoveController.h"
#include "catch.hpp"

TEST_CASE( "Move controller tests", "[moveController]" ) {
    MoveController controller;
    REQUIRE( controller.findPlayerPoint() == cocos2d::Vec2(0,0) );
    REQUIRE( controller.findPlayerPoint() == cocos2d::Vec2(1,0) );
}