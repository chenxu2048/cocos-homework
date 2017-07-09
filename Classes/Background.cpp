#include "Background.h"
#include "Variable.h"

USING_NS_CC;
using namespace CocosFlappyBird;

bool BackgroundBase::init() {
  INIT_LAYER();
  m_offset = Variable::getInstance()->getValue<float>(this->offsetName());
  m_visible_size = Director::getInstance()->getVisibleSize();
  const auto& filename = this->pictureName();
  auto background = Sprite::createWithSpriteFrameName(filename);
  background->setAnchorPoint(Vec2::ZERO);
  background->setPosition(Vec2::ZERO);
  m_backgrounds.pushBack(background);
  this->addChild(background);
  auto content_size = background->getContentSize();
  std::size_t frame_num = static_cast<std::size_t>(std::ceil(m_visible_size.width / content_size.width));

  for (std::size_t i = 1; i <= frame_num; i++) {
    background = Sprite::createWithSpriteFrameName(filename);
    background->setAnchorPoint(Vec2::ZERO);
    background->setPosition(content_size.width * i, 0);
    m_backgrounds.pushBack(background);
    this->addChild(background);
  }
  return true;
}

void BackgroundBase::startScroll() {
  if (!m_is_scrolled) {
    m_is_scrolled = true;
    schedule(schedule_selector(BackgroundBase::scroll), 0.1f);
  }
}

void BackgroundBase::stopScroll() {
  if (m_is_scrolled) {
    m_is_scrolled = false;
    unschedule(schedule_selector(BackgroundBase::scroll));
  }
}

void BackgroundBase::scroll(float dt) {
  for (auto& background : m_backgrounds) {
    background->setPositionX(background->getPositionX() - m_offset);
  }
  auto head = m_backgrounds.front();
  auto width = head->getContentSize().width;
  if (head->getPositionX() <= -width) {
    m_backgrounds.erase(0);
    head->setPositionX(m_backgrounds.back()->getPositionX() + width);
    m_backgrounds.pushBack(head);
  }
}

bool Land::init() {
  if (!BackgroundBase::init()) return false;
  m_height = m_backgrounds.front()->getContentSize().height;
  return true;
}

void Land::makePhysics() {
  auto pb = PhysicsBody::createBox(Size(Director::getInstance()->getVisibleSize().width, m_height), PhysicsMaterial(10000.f, 0.0f, 1.0f));
  pb->setPositionOffset({ 0, -m_height });
  pb->setCategoryBitmask(0x02);
  pb->setCollisionBitmask(0x02);
  pb->setContactTestBitmask(0x02);
  pb->setDynamic(false);
  this->setPhysicsBody(pb);
}