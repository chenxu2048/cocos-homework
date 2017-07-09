#pragma once
#ifndef RESOURCE_LOADER_H__
#define RESOURCE_LOADER_H__
#include <memory>
#include "cocos2d.h"
#include "SimpleAudioEngine.h"
namespace CocosFlappyBird {
  class ResourceLoader {
    public:
    static inline void loadEffectMusic(const std::string& filename) {
      std::string whole_path = "sounds/" + filename;
      CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(whole_path.c_str());
    }

    static inline void addAnimation(cocos2d::Animation* animation, const std::string& name) {
      cocos2d::AnimationCache::getInstance()->addAnimation(animation, name);
    }

    static cocos2d::Animation* createAnimation(const std::string& name, float delay, int loops, int num);
    static bool init();

    private:
    static bool loaded;
  };
}

#endif // !RESOURCE_LOADER_H__
