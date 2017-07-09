#include "Setting.h"
#include "Utility.h"
#include <fstream>
using namespace CocosFlappyBird;
using namespace std;
USING_NS_CC;

void SettingHelper::setVolume(int volume) {
  if (volume > 100 || volume < 0) return;
  if (volume <= 0) setMute();
  else setMute(false);
  m_setting["volume"] = volume;
}

SettingHelper::~SettingHelper() {
  ofstream file(m_path);
  m_setting >> file;
}

SettingHelper::SettingHelper(const std::string& path = SETTING_PATH): m_path(path), m_setting(nlohmann::json::parse(ifstream(path))) {
}

bool Setting::init() {
  INIT_LAYER()
  return true;
}