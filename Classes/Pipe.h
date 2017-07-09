#pragma once
#ifndef PIPE_H__
#define PIPE_H__
#include "cocos2d.h"
namespace CocosFlappyBird {
  class Pipe: public cocos2d::Node {
   public:
    CREATE_FUNC(Pipe)
    virtual bool init();
    bool collision(const cocos2d::Point& point);
    inline float getPipeWidth() const { return m_pipe_width; }
   private:
    cocos2d::Sprite *m_up, *m_down;
    float m_pipe_width;
  };

  class PipeLayer : public cocos2d::Layer {
   public:
    CREATE_FUNC(PipeLayer)
    void movePipe(float dt);
    void move();
    void stop();
    virtual bool init();
   private:
    cocos2d::Vector<Pipe *> m_pipes;
    float m_pipe_interval;
    float m_pipe_offset;
    std::mt19937 m_random_gen;
  };
}

#endif // !PIPE_H__
