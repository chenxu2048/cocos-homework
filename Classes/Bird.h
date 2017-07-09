#ifndef BIRD_H__
#define BIED_H__
#include "Utility.h"
#include "cocos2d.h"
namespace CocosFlappyBird {
  class Bird : public cocos2d::Layer {
   public:
    CREATE_FUNC(Bird);
    virtual bool init();
    void jump();
    void onHit();
    void fly();
    void stop();
   private:
    cocos2d::Sprite *m_bird;
    cocos2d::Vec2 m_bird_velocity;
    bool m_is_paused, m_is_dead;
  };
}

#endif // !BIRD_H__
