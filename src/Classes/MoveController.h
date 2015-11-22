#ifndef __MOVECONTROLLER_H__
#define __MOVECONTROLLER_H__

#include "cocos2d.h"

/*
 Holds objects positions and guarantees that
 their position will be valid related to each other.
 
 Provides API to control objects position.
 */
class MoveController
{
private:
    cocos2d::TMXTiledMap * map;
public:
    void movePlayer(cocos2d::Vec2 point);
    
    cocos2d::Vec2 findPlayerPoint();
    
};


#endif /* __MOVECONTROLLER_H__ */
