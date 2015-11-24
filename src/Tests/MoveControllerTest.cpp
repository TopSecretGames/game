#include "MoveController.h"
#include "fakeit.hpp"

using namespace fakeit;

class ExposedController : public tsg::move::MoveController {

public:
    virtual cocos2d::Vec2 getPlayerSpawn() const;
};

cocos2d::Vec2 ExposedController::getPlayerSpawn() const {
    return playerSpawn;
}

TEST_CASE( "That spawn point found and loaded well", "[MoveController]" ) {
    cocos2d::Vector<cocos2d::TMXObjectGroup*> groups;
    cocos2d::TMXObjectGroup group;
    group.setGroupName("spawn point");
    cocos2d::ValueVector v;
    cocos2d::ValueMap vp;
    vp["name"] = "spawn1";
    vp["x"] = cocos2d::Value(1.0f);
    vp["y"] = cocos2d::Value(2.0f);
    v.push_back(cocos2d::Value(vp));
    group.setObjects(v);
    groups.pushBack(&group);
    cocos2d::TMXTiledMap map;
    map.setObjectGroups(groups);

    ExposedController controller;
    controller.onMapLoad(&map);
    REQUIRE(controller.getPlayerSpawn() == cocos2d::Vec2(1.0f, 2.0f));
}
