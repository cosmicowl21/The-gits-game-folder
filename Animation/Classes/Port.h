/*#if CC_TARGET_PLATFORM == CC_PLATFORM_WP8
audioEngine->preloadBackgroundMusic("background.wav");
audioEngine->preloadEffect("jump.wav");
audioEngine->preloadEffect("crouch.wav");
audioEngine->preloadEffect("pickup_coin.wav");
#else
audioEngine->preloadBackgroundMusic("background.mp3");
audioEngine->preloadEffect("jump.mp3");
audioEngine->preloadEffect("crouch.mp3");
audioEngine->preloadEffect("pickup_coin.mp3");
#endif
Similarly, modify the code in runner.cpp, playscene.cpp files to use WAV files.

#if CC_TARGET_PLATFORM == CC_PLATFORM_WP8
audioEngine->playBackgroundMusic("jump.wav", true);
#else
audioEngine->playBackgroundMusic("jump.mp3", true);
#endif*/