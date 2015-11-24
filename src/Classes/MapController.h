#ifndef MAP_CONTROLLER_H
#define MAP_CONTROLLER_H
#include <string>
#include <tuple>
#include <vector>

#include "IMapEventListener.h"
namespace tsg {
    namespace map {
        class MapController{
            std::string mapsRoot;
            std::vector<IMapEventListener*> mapEventListeners;
            cocos2d::TMXTiledMap *currentMap;
            typedef std::tuple<std::string, std::string> MapType;
            typedef std::vector<MapType> MapCollection;
            void notifyListeners();
            
        protected:
            
        public:
            virtual void loadMapFromFile(const std::string&);
            MapController(const MapController &);
            MapController();
            MapController(std::string);
            MapCollection getMaps();
            void loadMap(std::string);
            void registerListener(IMapEventListener*); 
        };
    }
}
#endif

