#ifndef __MOVECONTROLLER_H__
#define __MOVECONTROLLER_H__

#include "cocos2d.h"

/*
 Holds objects positioning and guarantees that
 their position will be valid to each other.
 
 Provides API to control objects position.
 */
class MoveController
{
private:
    cocos2d::TMXTiledMap * map;
public:
    /*Moves out current user's player to specified point*/
    void movePlayer(cocos2d::Vec2 point);

    /*Returns current user's player point*/
    cocos2d::Vec2 findPlayerPoint();
    
    void onMapLoaded(cocos2d::TMXTiledMap * map);
};


#endif /* __MOVECONTROLLER_H__ */
