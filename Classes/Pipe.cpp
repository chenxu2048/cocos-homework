#include "Pipe.h"
#include "Variable.h"
#include "cocos2d.h"
#include "Utility.h"
using namespace CocosFlappyBird;
USING_NS_CC;

bool Pipe::init() {
  if (!Node::init()) return false;
  float scale_ratio = Variable::getInstance()->getValue<float>("pipe_scale_ratio");
  m_up = Sprite::createWithSpriteFrameName("pipe_up.png");
  m_up->setScale(scale_ratio);
  m_up->setAnchorPoint(Vec2(0.5f, 1));
  m_down = Sprite::createWithSpriteFrameName("pipe_down.png");
  m_down->setScale(scale_ratio);
  m_down->setAnchorPoint(Vec2(0.5f, 0));
  this->addChild(m_up, 0);
  this->addChild(m_down, 0);
  auto up_pb = PhysicsBody::createBox(m_up->getContentSize(), PhysicsMaterial(0.0f, 0.0f, 1.0f));
  up_pb->setCategoryBitmask(0x01);
  up_pb->setCollisionBitmask(0x01);
  up_pb->setContactTestBitmask(0x01);
  up_pb->setDynamic(false);
  m_up->setPhysicsBody(up_pb);
  auto down_pb = PhysicsBody::createBox(m_up->getContentSize(), PhysicsMaterial(0.0f, 0.0f, 1.0f));
  down_pb->setCategoryBitmask(0x01);
  down_pb->setCollisionBitmask(0x01);
  down_pb->setContactTestBitmask(0x01);
  down_pb->setDynamic(false);
  m_down->setPhysicsBody(down_pb);
  float slot_width = Variable::getInstance()->getValue<float>("pipe_width_ratio") * m_up->getContentSize().width;
  m_up->setPosition(0.0f, -slot_width / 2);
  m_down->setPosition(0.0f, slot_width / 2);
  auto pb = PhysicsBody::createBox({ 1, slot_width }, PhysicsMaterial(0.0f, 0.0f, 0.0f));
  pb->setCategoryBitmask(0x05);
  pb->setContactTestBitmask(0x05);
  pb->setCollisionBitmask(0x00);
  // Ö»½Ó´¥£¬ ²»Åö×²
  pb->setDynamic(false);
  this->setPhysicsBody(pb);
  return true;
}

bool Pipe::collision(const Point& point) {
  return m_up->getBoundingBox().containsPoint(point) ||
    m_down->getBoundingBox().containsPoint(point);
}

bool PipeLayer::init() {
  INIT_LAYER()
  auto visible_size = Director::getInstance()->getVisibleSize();
  auto variables = Variable::getInstance();
  m_pipe_offset = variables->getValue<float>("pipe_speed");
  m_random_gen = std::mt19937(std::random_device()());
  std::uniform_real_distribution<> ud(-50, 50);
  m_pipe_interval = variables->getValue<float>("pipe_interval");
  size_t pipe_num = visible_size.width / m_pipe_interval;
  for (size_t i = 0; i <= pipe_num; ++i) {
    auto pipe = Pipe::create();
    pipe->setPosition(visible_size.width * 1.8f + i * m_pipe_interval, static_cast<float>(ud(m_random_gen)));
    this->addChild(pipe);
    m_pipes.pushBack(pipe);
  }
  return true;
}

void PipeLayer::movePipe(float dt) {
  for (auto pipe : m_pipes) {
    pipe->setPositionX(pipe->getPositionX() - m_pipe_offset);
  }
  auto head = m_pipes.front();
  if (head->getPositionX() <= -head->getPipeWidth()) {
    m_pipes.erase(0);
    std::uniform_real_distribution<> ud(-50, 50);
    head->setPosition(m_pipes.back()->getPositionX() + m_pipe_interval, ud(m_random_gen));
    m_pipes.pushBack(head);
  }
}

void PipeLayer::move() {
  schedule(schedule_selector(PipeLayer::movePipe), 0.1f);
}

void PipeLayer::stop() {
  unschedule(schedule_selector(PipeLayer::movePipe));
}