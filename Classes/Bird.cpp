#include "cocos2d.h"
#include "Bird.h"
#include "Variable.h"
#include "SimpleAudioEngine.h"
using namespace CocosFlappyBird;
USING_NS_CC;

bool Bird::init() {
  INIT_LAYER()
  m_bird = Sprite::createWithSpriteFrameName("bird0_0.png");
  auto visible_size = Director::getInstance()->getVisibleSize();
  m_bird->setPosition(visible_size.width / 2, 0);
  m_bird->setScale(0.7f);
  auto pb = PhysicsBody::createCircle(m_bird->getContentSize().width / 2.5, PhysicsMaterial(Variable::getInstance()->getValue<float>("bird_mass"), 0.0f, 1.0f));
  pb->setAngularVelocityLimit(0);
  pb->setCategoryBitmask(0x03);
  pb->setCollisionBitmask(0x03);
  pb->setContactTestBitmask(0x03);
  pb->setDynamic(true);
  m_bird->setPhysicsBody(pb);
  this->addChild(m_bird);
  m_bird_velocity = Vec2::ZERO;
  m_is_dead = false;
  m_is_paused = true;
  return true;
}

void Bird::fly() {
  if (m_is_paused) return;
  m_is_paused = true;
  auto pb = m_bird->getPhysicsBody();
  m_bird_velocity = pb->getVelocity();
  pb->setDynamic(true);
  pb->setVelocity(Vec2::ZERO);
}

void Bird::stop() {
  if (!m_is_paused) return;
  m_is_paused = false;
  auto pb = m_bird->getPhysicsBody();
  pb->setVelocity(m_bird_velocity);
  pb->setDynamic(false);
}

void Bird::onHit() {
  CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sounds/sfx_die.mp3");
}

void Bird::jump() {
  auto bp = m_bird->getPhysicsBody();
  CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sounds/sfx_wing.mp3");
  m_bird->runAction(Animate::create(AnimationCache::getInstance()->getAnimation("bird0")));
  bp->setVelocity(Vec2(0, 100));
}