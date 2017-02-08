
#include "AppDelegate.h"
#include "GameScene.h"

USING_NS_CC;

static cocos2d::Size designResolutionSize = cocos2d::Size(1000, 480);
static cocos2d::Size smallResolutionSize = cocos2d::Size(480, 320);
static cocos2d::Size mediumResolutionSize = cocos2d::Size(1024, 768);
static cocos2d::Size largeResolutionSize = cocos2d::Size(2048, 1536);

AppDelegate::AppDelegate() 
{

}

AppDelegate::~AppDelegate()
{
}

void AppDelegate::initGLContextAttrs()
{

	GLContextAttrs glContextAttrs = { 8, 8, 8, 8, 24, 8 };

	GLView::setGLContextAttrs(glContextAttrs);
}

static int register_all_packages()
{
	return 0; //flag for packages manager
}

bool AppDelegate::applicationDidFinishLaunching()
{
	// initialize director
	auto director = Director::getInstance();
	auto glview = director->getOpenGLView();

	if (!glview)
	{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
		glview = GLViewImpl::createWithRect("HomeRun", Rect(0, 0, designResolutionSize.width, designResolutionSize.height));
#else
		glview = GLViewImpl::create("HomeRun");
#endif
		director->setOpenGLView(glview);
	}

	if (!glview)
	{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		glview = GLViewImpl::createWithRect("HomeRun", Rect(0, 0, smallResolutionSize.width, smallResolutionSize.height));
#endif
	}

	director->setDisplayStats(true);

	director->setAnimationInterval(1.0 / 60);

	register_all_packages();

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("solbrain.plist");
	AnimationCache::getInstance()->addAnimationsWithFile("solbrain-animations.plist");

	auto scene = GameScene::createScene();

	director->runWithScene(scene);

	return true;
}

void AppDelegate::applicationDidEnterBackground()
{
	Director::getInstance()->stopAnimation();

	// if you use SimpleAudioEngine, it must be pause
	// SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() 
{
	Director::getInstance()->startAnimation();


	// if you use SimpleAudioEngine, it must resume here
	// SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}