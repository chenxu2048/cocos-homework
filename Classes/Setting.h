#pragma once
#ifndef SETTING_H__
#define SETTING_H__
#include "json.hpp"
#include "cocos2d.h"
namespace CocosFlappyBird {
  static constexpr char * SETTING_PATH = "setting.json";
  class SettingHelper {
   public:
    SettingHelper(const std::string &path);
    inline void setMute(bool mute = true) { m_setting["mute"] = mute; }
    inline void toggleMute(bool mute) { m_setting["mute"] = !m_setting["mute"].get<bool>(); }
    void setVolume(int volume);
    inline bool getMute() { return m_setting["mute"].get<bool>(); }
    inline int getVolume() { return m_setting["volume"].get<int>(); }
    ~SettingHelper();
   private:
    nlohmann::json m_setting;
    std::string m_path;
  };

  class Setting : public cocos2d::Layer {
   public:
    CREATE_FUNC(Setting)
    virtual bool init();

  };
}
#endif // !SETTING_H__
