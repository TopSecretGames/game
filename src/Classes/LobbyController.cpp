#include "LobbyController.h"
#include <iostream>

namespace tsg {
namespace lobby {
using cocos2d::Vec2;

void LobbyController::onInit() {
  this->scene = cocos2d::Scene::create();
  scene->addChild(this);
  cocos2d::Director::getInstance()->runWithScene(scene);
}

bool LobbyController::init() {
  if (!Layer::init()) {
    return false;
  }
  cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
  Vec2 origin = cocos2d::Director::getInstance()->getVisibleOrigin();

  auto background = cocos2d::Sprite::create("data/background.jpg");
  background->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

  cocos2d::Size backgroundSize = background->getContentSize();
  background->setScaleX(visibleSize.width / backgroundSize.width);
  background->setScaleY(visibleSize.height / backgroundSize.height);
  this->addChild(background, 0);

  auto startButton = cocos2d::MenuItemImage::create(
      "data/Start_Button_0.png",
      "data/Start_Button_Pressed_0.png",
      CC_CALLBACK_1(LobbyController::startGame, this));

  startButton->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
  startButton->setScale(0.8);
  // create menu, it's an autorelease object
  auto menu = cocos2d::Menu::create(startButton, NULL);
  menu->setPosition(Vec2::ZERO);
  this->addChild(menu, 1);
  return true;
}

void LobbyController::onUpdate(float delta) {

}

void LobbyController::registerListener(ILobbyEventListener *listener) {
  if (listener != nullptr) {
    this->listeners.push_back(listener);
  }
}

void LobbyController::startGame(cocos2d::Ref *pSender) {
  for_each(listeners.begin(), listeners.end(),
           [](ILobbyEventListener *l) { l->onStartGame(); });
}

}
}
