#pragma once
#ifndef VARIABLE_H__
#define VARIABLE_H__
#include <memory>
#include "json.hpp"
#include "cocos2d.h"

static constexpr char* CONFIG_PATH = "config.json";

namespace CocosFlappyBird {
  class Variable {
   public:
    template <typename Ret = std::string>
    inline Ret getValue(const std::string& key) {
      return m_data[key].get<Ret>();
    }

    static inline std::shared_ptr<Variable> getInstance() {
      if (m_instance == nullptr) {
        m_instance.reset(new Variable(CONFIG_PATH));
      }
      return m_instance;
    }
   private:
    nlohmann::json m_data;
    Variable(const std::string& filepath);

    Variable(const Variable&) = delete;
    Variable operator=(const Variable&) = delete;
    static std::shared_ptr<Variable> m_instance;
  };
}

#endif // !VARIABLE_H__
