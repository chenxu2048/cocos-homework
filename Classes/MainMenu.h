#pragma once
#ifndef MAIN_MENU_H__
#define MAIN_MENU_H__
#include "cocos2d.h"
#include "Background.h"
#include "Utility.h"
namespace CocosFlappyBird {
  class MainMenu : public cocos2d::Layer {
   public:
    CREATE_SCENE(MainMenu)
    CREATE_FUNC(MainMenu)
    virtual bool init();
    void startGameCallback(cocos2d::Ref* pSender);
    void settingCallaback(cocos2d::Ref* pSender);
    void touchCallback(cocos2d::Touch *touch, cocos2d::Event *event);
   private:
    Background* m_background;
    Land* m_land;
    cocos2d::Sprite *m_start_btn;
    cocos2d::Sprite *m_setting_btn;
    bool m_can_touch;
  };
}

#endif // !MAIN_MENU_H__
