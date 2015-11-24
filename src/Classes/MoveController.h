#ifndef __MOVECONTROLLER_H__
#define __MOVECONTROLLER_H__

#include "IMapEventListener.h"
#include "cocos2d.h"

/*
 Holds objects positioning and guarantees that
 their position will be valid to each other.
 
 Provides API to control objects position.
 */
namespace tsg {
    namespace move {
        class MoveController : public map::IMapEventListener {
        private:
            cocos2d::TMXTiledMap * map;
        public:
            virtual void onMapLoad(cocos2d::TMXTiledMap*) override;
        };
    }
}
#endif /* __MOVECONTROLLER_H__ */
