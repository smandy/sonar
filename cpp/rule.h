#pragma once

#include "sonar.h"
#include <memory>

class Rule;

using RulePtr = std::unique_ptr<Rule>;

class Rule {
    const std::string id;
    
 public:
 Rule( const std::string& s) : id(s) {
        std::cout << "Rule " << s << std::endl;
    }
 
    const std::string& getId() { return id; }

    virtual void check(sonar::ServerStatus &status) = 0;

    virtual std::string desc() = 0;
    
    virtual ~Rule() {
        std::cout << "~Rule " << getId() << std::endl;
    };
};



