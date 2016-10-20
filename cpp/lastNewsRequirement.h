#pragma once

#include "rule.h"
#include <memory>

class LastNewsRequirement : public Rule {
 public:
    static RulePtr parse( std::vector<std::string> xs);
    LastNewsRequirement(std::string s);
    
    void check(sonar::ServerStatus &status);
    virtual std::string desc();
};
