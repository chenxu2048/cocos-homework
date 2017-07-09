#pragma once
#ifndef GAME_SCENE_H__
#define GAME_SCENE_H__

#include "cocos2d.h"
#include "Bird.h"
#include "Pipe.h"
#include "Background.h"
#include "Utility.h"
#include <random>

namespace CocosFlappyBird {
  class GameScene :public cocos2d::Layer {
   public:
    static cocos2d::Scene *createScene();
    CREATE_FUNC(GameScene)
    virtual bool init();
    void touchHandler(cocos2d::Touch *touch, cocos2d::Event *event);
    bool collisionHandler(cocos2d::PhysicsContact &contact);
   private:
    void resumeGame();
    void startGame();
    void pauseGame();
    void gameOver();
    void addScore();
    void gameExit();
    cocos2d::PhysicsWorld* m_world;
    Bird *m_bird;
    Background *m_background;
    PipeLayer *m_pipes;
    Land *m_land;
    bool m_can_touch, m_can_game, m_is_paused;
    int m_score;
    cocos2d::LabelBMFont *m_score_panel;
    cocos2d::Sprite *m_new, *m_exit, *m_panel;
  };
}

#endif // !GAME_SCENE_H__
