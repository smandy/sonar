#include "lastNewsRequirement.h"

LastNewsRequirement::LastNewsRequirement(std::string s) : Rule(s){};

RulePtr LastNewsRequirement::parse(std::vector<std::string>)
{
    return std::make_unique<LastNewsRequirement>("woot2");
};

void LastNewsRequirement::check(sonar::ServerStatus&){};

std::string LastNewsRequirement::desc()
{
    return "LastNewsRequirement";
};
