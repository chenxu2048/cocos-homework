#include "Variable.h"
#include <fstream>
using namespace CocosFlappyBird;
std::shared_ptr<Variable> Variable::m_instance = nullptr;

Variable::Variable(const std::string & filepath): m_data(nlohmann::json::parse(std::ifstream(filepath))) {
}
