#include "GameScene.h"
#include "Variable.h"
using namespace CocosFlappyBird;
USING_NS_CC;

Scene* GameScene::createScene() {
  auto scene = Scene::createWithPhysics();
#undef DEBUG
#ifdef DEBUG
  // Debug 模式
  // 开启debug模式需要setAutoStep(true) 并注释掉update函数第一行
  scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
  scene->getPhysicsWorld()->setAutoStep(true);
#else
  scene->getPhysicsWorld()->setAutoStep(false);
#endif // DEBUG

  scene->getPhysicsWorld()->setGravity(Vec2(0, -300.0f));
  auto layer = GameScene::create();
  layer->m_world = scene->getPhysicsWorld();
  scene->addChild(layer);
  return scene;
}

bool GameScene::init() {
  INIT_LAYER()
  m_can_touch = true;
  m_can_game = true;
  auto listener = EventListenerTouchOneByOne::create();
  listener->onTouchEnded = CC_CALLBACK_2(GameScene::touchHandler, this);
  listener->onTouchBegan = [&](auto, auto) {
    if (!this->m_can_touch) return false;
    this->m_can_touch = false;
    return true;
  };
  this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
  auto visible_size = Director::getInstance()->getVisibleSize();

  auto collision = EventListenerPhysicsContact::create();
  collision->onContactBegin = CC_CALLBACK_1(GameScene::collisionHandler, this);
  this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(collision, this);

  m_background = Background::create();
  this->addChild(m_background, 0);
  m_land = Land::create();
  this->addChild(m_land, 2);
  m_land->makePhysics();

  m_pipes = PipeLayer::create();
  m_pipes->setPosition(0, (visible_size.height + m_land->getHeight()) / 2);
  this->addChild(m_pipes, 1);
  m_bird = Bird::create();
  m_bird->setPosition(0, (visible_size.height + m_land->getHeight()) / 2);
  this->addChild(m_bird);
  startGame();
#ifndef DEBUG
  schedule([=](auto) {
    this->getScene()->getPhysicsWorld()->step(0.01f);
  }, 0.01f, "physics_step");
#endif // !DEBUG
  m_score = 0;
  m_score_panel = LabelBMFont::create(std::to_string(m_score), "fonts/score.fnt", 0.0f, TextHAlignment::CENTER);
  m_score_panel->setPosition(visible_size.width / 2, visible_size.height * 0.96f);
  m_score_panel->setAnchorPoint({ 0.5, 1 });
  this->addChild(m_score_panel, 10);
  m_exit = m_new = nullptr;
  startGame();
  return true;
}

void GameScene::startGame() {
  m_background->startScroll();
  m_land->startScroll();
  m_pipes->move();
  m_bird->fly();
}

void GameScene::pauseGame() {
  this->pause();
  m_background->stopScroll();
  m_land->stopScroll();
  m_pipes->stop();
  m_bird->stop();
}

void GameScene::resumeGame() {
  this->resume();
  this->startGame();
}


void GameScene::touchHandler(Touch *touch, Event *event) {
  m_can_touch = true;
  auto point = touch->getLocation();
  if (m_can_game && !m_is_paused) {
    m_can_game = false;
    scheduleOnce([=](auto) {
      this->m_can_game = true;
    }, 0.1f, "bird_click_interval");
    m_bird->jump();
  } else if (m_new != nullptr && m_exit != nullptr && m_is_paused) {
    point = m_panel->convertToNodeSpace(point);
    if (m_new->getBoundingBox().containsPoint(point)) {
      Director::getInstance()->replaceScene(GameScene::createScene());
    } else if (m_exit->getBoundingBox().containsPoint(point)) {
      gameExit();
    }
  }
}

bool GameScene::collisionHandler(PhysicsContact &contact) {
  if (m_is_paused) return true;
  auto body_a = contact.getShapeA()->getBody();
  auto body_b = contact.getShapeB()->getBody();
  if (body_a->getCategoryBitmask() == 0x03 || body_b->getCategoryBitmask() == 0x03) {
    if (body_a->getCategoryBitmask() == 0x05 || body_b->getCategoryBitmask() == 0x05) {
      this->addScore();
    } else {
      this->gameOver();
    }
  }
  return true;
}

void GameScene::gameOver() {
  m_bird->onHit();
  m_is_paused = true;
  m_background->stopScroll();
  m_land->stopScroll();
  m_pipes->stop();
  m_score_panel->removeFromParent();
  auto score_panel = Sprite::createWithSpriteFrameName("score_panel.png");
  score_panel->setAnchorPoint({ 0.5f, 0.5f });
  score_panel->setPosition(Director::getInstance()->getVisibleSize() / 2);
  auto score_label = LabelBMFont::create("0", "fonts/score.fnt", 0.0f, TextHAlignment::CENTER);
  int max_score = UserDefault::getInstance()->getIntegerForKey("max_score", 0);
  if (m_score > max_score) {
    max_score = m_score;
    UserDefault::getInstance()->setIntegerForKey("max_score", max_score);
  }
  auto score_panel_size = score_panel->getContentSize();
  score_panel->addChild(score_label);
  score_label->setPosition(score_panel_size.width * 0.8f, score_panel_size.height * 0.58f);
  auto max_score_label = LabelBMFont::create(std::to_string(max_score), "fonts/score.fnt", 0.0f, TextHAlignment::CENTER);
  score_panel->addChild(max_score_label);
  max_score_label->setPosition(score_panel_size.width * 0.8f, score_panel_size.height * 0.26f);
  this->addChild(score_panel, 10);
  schedule([=](auto) {
    int cur_score = std::atoi(score_label->getString().c_str()) + 1;
    if (cur_score > m_score) {
      int rank = 3;
      if (m_score > 100) {
        rank = 1;
      } else if (m_score > 60) {
        rank = 0;
      } else if (m_score > 30) {
        rank = 2;
      }
      auto medal = Sprite::createWithSpriteFrameName(StringUtils::format("medals_%d.png", rank));
      medal->setPosition(score_panel_size.width * 0.24f, score_panel_size.height * 0.46f);
      medal->setAnchorPoint({ 0.5f, 0.5f });
      score_panel->addChild(medal);
      unschedule("add_score");
      m_new = Sprite::createWithSpriteFrameName("new.png");
      m_exit = Sprite::createWithSpriteFrameName("close.png");
      m_exit->setPosition(score_panel_size * 0.95f);
      m_new->setPosition(score_panel_size.width * 0.5f, score_panel_size.height * 0.2f);
      score_panel->addChild(m_new);
      score_panel->addChild(m_exit);
    } else {
      score_label->setString(std::to_string(cur_score));
    }
  }, 0.15f, "add_score");
  m_panel = score_panel;
}

void GameScene::addScore() {
  m_score++;
  m_score_panel->setString(std::to_string(m_score));
}

void GameScene::gameExit() {
  Director::getInstance()->popScene();
}