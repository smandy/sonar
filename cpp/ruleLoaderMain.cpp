#include "ruleLoader.h"

int main( int argc, char *argv[]) {
    const auto rules = RuleLoader::parseRules("../config/rules.txt");
    for( auto& rule : rules) {
        std::cout << "Ruls is " << rule->desc() << " " << rule->getId() << std::endl;
    };
    std::cout << "Falling off end of main. (Rules about to go out of scope" << std::endl;
};
