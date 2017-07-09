#pragma once
#ifndef AUDIO_H__
#define AUDIO_H__
#include "SimpleAudioEngine.h"
#include "cocos2d.h"
class Audio {
  public:
  enum EffectName {
    Hit,
    Die,
    Point,
    Swooshing,
    Wing,
  };
  Audio() {}
  void setVolumn(float volumn);
  void playEffect();
};

#endif // !AUDIO_H__
