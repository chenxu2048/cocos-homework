#include "ResourceLoader.h"
#include "Variable.h"
using namespace CocosFlappyBird;
USING_NS_CC;

bool ResourceLoader::loaded = false;
Animation * ResourceLoader::createAnimation(const std::string & name, float delay, int loops, int num=std::numeric_limits<int>::max()) {
  auto cache = SpriteFrameCache::getInstance();
  Vector<SpriteFrame*> frames;
  for (int i = 0; i < num; ++i) {
    const auto&& frame_name = StringUtils::format("%s_%d.png", name.c_str(), i);
    auto one_frame = cache->getSpriteFrameByName(frame_name);
    if (one_frame == nullptr) {
      break;
    }
    frames.pushBack(one_frame);
  }
  auto ret = Animation::createWithSpriteFrames(frames);
  ret->setDelayPerUnit(delay);
  ret->setRestoreOriginalFrame(true);
  ret->setLoops(loops);
  return ret;
}

bool CocosFlappyBird::ResourceLoader::init() {
  const auto&& variables = Variable::getInstance();
  SpriteFrameCache::getInstance()->addSpriteFramesWithFile(variables->getValue("flappy_bird_plist"));
  const char* effect_sounds[] = {
    "hit",
    "die",
    "point",
    "swooshing",
    "wing"
  };
  for (const auto& name : effect_sounds) {
    ResourceLoader::loadEffectMusic(variables->getValue(name));
  }
  const auto&& delay = variables->getValue<float>("bird_animation_delay");
  for (int i = 0; i < 2; ++i) {
    const auto&& name = StringUtils::format("bird%d", i);
    ResourceLoader::addAnimation(ResourceLoader::createAnimation(name, delay, -1), name);;
  }
  return true;
}
