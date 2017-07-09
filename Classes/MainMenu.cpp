#include "MainMenu.h"
#include "Background.h"
#include "GameScene.h"
USING_NS_CC;
using namespace CocosFlappyBird;

bool MainMenu::init() {
  INIT_LAYER()
  auto visible_size = Director::getInstance()->getVisibleSize();
  auto background = Background::create();
  background->startScroll();
  this->addChild(background);
  auto land = Land::create();
  land->startScroll();
  this->addChild(land);
  m_can_touch = true;
  m_start_btn = Sprite::createWithSpriteFrameName("button_play.png");
  m_start_btn->setPosition(visible_size / 2);
  m_setting_btn = Sprite::createWithSpriteFrameName("setting.png");
  m_setting_btn->setPosition(visible_size - m_setting_btn->getContentSize() * 1.02f);
  this->addChild(m_start_btn);
  this->addChild(m_setting_btn);
  auto listener = EventListenerTouchOneByOne::create();
  listener->onTouchEnded = CC_CALLBACK_2(MainMenu::touchCallback, this);
  listener->onTouchBegan = [&](Touch*, Event*)->bool {
    if (!this->m_can_touch) return false;
    this->m_can_touch = false;
    return true;
  };
  auto title = Sprite::createWithSpriteFrameName("title.png");
  title->setAnchorPoint({ 0.5f, 0.5f });
  title->setPosition(visible_size.width / 2, visible_size.height * 0.7f);
  this->addChild(title);
  this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
  return true;
}

void MainMenu::startGameCallback(Ref* pSender) {
  Director::getInstance()->pushScene(GameScene::createScene());
}

void MainMenu::settingCallaback(Ref* pSender) {

}

void MainMenu::touchCallback(cocos2d::Touch * touch, cocos2d::Event * event) {
  m_can_touch = true;
  auto position = touch->getLocation();
  if (m_start_btn->getBoundingBox().containsPoint(position)) {
    startGameCallback(m_start_btn);
  } else if (m_setting_btn->getBoundingBox().containsPoint(position)) {
    settingCallaback(m_setting_btn);
  }
}
