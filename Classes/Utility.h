#pragma once
#ifndef UTILITY_H__
#define UTILITY_H__
#include "cocos2d.h"

#ifndef CREATE_SCENE
#define CREATE_SCENE(__TYPE__) \
  static cocos2d::Scene* createScene() { \
    auto scene = cocos2d::Scene::create(); \
    auto layer = __TYPE__::create(); \
    scene->addChild(layer); \
    return scene; \
  }

#endif // !CREATE_SCENE

#ifndef INIT_LAYER
#define INIT_LAYER() \
   if (!Layer::init()) { \
     return false; \
   }

#endif // !INIT_LAYER


#endif // !UTILITY_H__
