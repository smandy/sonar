#include "lastNewsRequirement.h"

LastNewsRequirement::LastNewsRequirement(std::string s) : Rule(s) {};

RulePtr LastNewsRequirement::parse(std::vector<std::string> xs) {
  return std::make_unique<LastNewsRequirement>("woot2");
};

void LastNewsRequirement::check(sonar::ServerStatus &status) {};

std::string LastNewsRequirement::desc() {
  return "LastNewsRequirement";
};
