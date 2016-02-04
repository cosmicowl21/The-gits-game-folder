#include "SplashScene.h"
#include "MainMenuScene.h"
#include "Definitions.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;

USING_NS_CC;
#define SPLASH_SCREEN_SOUND_SFX "Super Happy Funtime.mp3"//sound for the splash screen
Scene* SplashScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
	auto layer = SplashScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool SplashScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	this->scheduleOnce(schedule_selector(SplashScene::goToMainMenuScene), DISPLAY_TIME_SPLASH_SCENE);//going to the main menu 

	auto backgroundSprite = Sprite::create("Super happy funtime studios.png");//image for the splash screen 
	backgroundSprite->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(backgroundSprite);
	SimpleAudioEngine::getInstance()->playEffect(SPLASH_SCREEN_SOUND_SFX);//splash scrren 

	return true;

}

void SplashScene::goToMainMenuScene(float dt)
{
	auto scene = MainMenuScene::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(TRANSATION_TIME, scene));

}

