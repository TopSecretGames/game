#include "GameController.h"

USING_NS_CC;

enum
{
    kTagTileMap = 1,
};

Scene* GameController::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = GameController::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameController::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto map = TMXTiledMap::create("data/map1.tmx");
    auto sprite = Sprite::create();
    auto s = map->getContentSize();
    float scale = 1.5;
    auto center = Vec2((getContentSize().width/2 - s.width/2) * scale, (getContentSize().height/2 - s.height/2) * scale);
    
    
    auto listener = cocos2d::EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    
    listener->onTouchBegan = [=](cocos2d::Touch* touch, cocos2d::Event* event)
    {
        return true;
    };
    
    listener->onTouchEnded = [=](cocos2d::Touch* touch, cocos2d::Event* event)
    {
    };
    
    listener->onTouchMoved = [=](cocos2d::Touch* touch, cocos2d::Event* event)
    {
//        auto c = map->convertTouchToNodeSpace(touch);
        auto c = touch->getStartLocation();
        auto d = Vec2(touch->getLocation().x, touch->getLocation().y);
        d.subtract(c);
        d.normalize();
        setPosition(getPosition() + d * 5.0);
        CCLOG("touch move at %f,%f",d.x,d.y);
    };

    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(listener, 30);
    

    CCLOG("ContentSize: %f, %f", s.width,s.height);
    CCLOG("Origin: %f, %f", origin.x, origin.y);
    CCLOG("Visible size: %f, %f", visibleSize.width, visibleSize.height);
    

    setScale(scale);

	this->addChild(map, 1, kTagTileMap);
    
    auto point = map->getObjectGroup("spawn point")->getObject("spawn1");
    auto spawnVector = Vec2(point["x"].asFloat(), point["y"].asFloat());

    CCLOG("content size %f,%f", getContentSize().width, getContentSize().height);
    CCLOG("map content size %f,%f", s.width, s.height);
    CCLOG("center is %f,%f", center.x, center.y);

    setPosition(center);

    
    map->addChild(sprite);
    
    
    Vector<SpriteFrame*> animFrames(10);
    for (int i=0; i < 10; ++i) {
        auto frame = SpriteFrame::create(
                                         "data/characters/knight/IDLE/0.png",
                                         Rect(i*67,0,67,137),
                                         false,
                                         Vec2::ZERO,
                                         Size(Vec2(67,137)));
        animFrames.pushBack(frame);
    }

    auto animation = Animation::createWithSpriteFrames(animFrames, 0.1f);
    auto animate = Animate::create(animation);
    auto repeatAnimate = RepeatForever::create(animate);
    sprite->runAction(repeatAnimate);
    
    
//    auto batch = SpriteBatchNode::create("data/characters/knight/IDLE/0.png");
//    auto sprite = Sprite::createWithTexture(batch->getTexture(), Rect(0,0,64,147));
//    sprite->setPosition(center);
//    map->addChild(sprite);

    //
//    
//    auto k = center - spawnVector;
//    k.normalize();
//    setPosition(center + k * spawnVector.distance(center));
    

//    map->setPosition();
    CCLOG("position: %f, %f", map->getPosition().x,map->getPosition().y);
	// all tiles are aliased by default, let's set them anti-aliased
//	for (const auto& child : map->getChildren()) {
//		static_cast<SpriteBatchNode*>(child)->getTexture()->setAntiAliasTexParameters();
//	}

    
    return true;
}


void GameController::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
