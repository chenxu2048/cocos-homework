#pragma once
#ifndef BACKGROUND_H__
#define BACKGROUND_H__

#include "cocos2d.h"
#include "Utility.h"
namespace CocosFlappyBird {
  class BackgroundBase : public cocos2d::Layer {
   public:
    CREATE_FUNC(BackgroundBase)
    virtual bool init();

    void startScroll();
    void stopScroll();
   protected:
    cocos2d::Vector<cocos2d::Sprite*> m_backgrounds;
   private:
    void scroll(float);
    cocos2d::Size m_visible_size;
    bool m_is_scrolled;
    
    float m_offset;
   public:
   virtual std::string offsetName() const { return ""; }
   virtual std::string pictureName() const { return ""; }
  };

  class Land : public BackgroundBase {
   public:
   virtual bool init();
    virtual inline std::string offsetName() const {
      return "background_speed";
    }
    virtual inline std::string pictureName() const {
      return "land.png";
    }
    void makePhysics();
    inline float getHeight() const { return m_height; }
    CREATE_FUNC(Land);
   private:
    float m_height;
  };
  class Background : public BackgroundBase {
   public:
    virtual inline bool init() {
     m_is_day = true;
     return BackgroundBase::init();
    }
    virtual inline std::string offsetName() const {
      return "background_speed";
    }
    virtual inline std::string pictureName() const {
      return m_is_day ? "bg_day.png" : "bg_night.png";
    }
    void toggle() {
      m_is_day = !m_is_day;
      const std::string& pic_name = this->pictureName();
      for (auto& background : m_backgrounds) {
        background->setSpriteFrame(pic_name);
      }
    }
    CREATE_FUNC(Background);
   private:
    bool m_is_day;
  };
}

#endif // !BACKGROUND_H__
