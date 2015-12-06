#pragma once

#include "IGameEventListener.h"
#include "ILobbyEventListener.h"
#include "cocos2d.h"

namespace tsg {
namespace lobby {

class LobbyController : public cocos2d::Layer, public tsg::game::IGameEventListener {
 public:
    virtual void onInit();
    virtual void onUpdate(float);
    void registerListener(ILobbyEventListener* listener);
    CREATE_FUNC(LobbyController);
 protected:
    virtual bool init();
    cocos2d::Scene* scene;
    std::vector<ILobbyEventListener*> listeners;
    void notifyListeners();
    void startGame(cocos2d::Ref* pSender);
};
}
}
