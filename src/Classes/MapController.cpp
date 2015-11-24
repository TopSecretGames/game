#include "MapController.h"
#include <iostream>

namespace tsg {
    namespace map {
        MapController::MapController() : mapsRoot("data/") {};
        MapController::MapController(const MapController& )
        : mapsRoot(""), currentMap(nullptr) {};
        
        MapController::MapController(std::string root) : mapsRoot(root) {};
        
        void MapController::registerListener(IMapEventListener* listener) {
            this->mapEventListeners.push_back(listener);
        };
        
        void MapController::loadMapFromFile(const std::string& map) {
            auto path = mapsRoot + map;
            this->currentMap = cocos2d::TMXTiledMap::create(path);
        }
        
        void MapController::notifyListeners() {
            for (auto listener : mapEventListeners) listener->onMapLoad(this->currentMap);
        }
        
        void MapController::loadMap(std::string map) {
            loadMapFromFile(map);
            notifyListeners();
        }
        
        MapController::MapCollection MapController::getMaps() {
            std::vector<MapType> collection;
            collection.push_back(std::make_tuple("FirstMap", "map1.tmx"));
            return collection;
        }
    }
}
