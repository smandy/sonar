#include "rule.h"
#include <memory>
#include <ostream>

class UptimeRequirement : public Rule {

    std::string startTime;
    std::string endTime;
    
 public:
    
 UptimeRequirement(const std::string& s,
                   const std::string& st,
                   const std::string et) :
    Rule {s},
        startTime {st}, endTime {et} {};
    static RulePtr parse( std::vector<std::string> xs) {
        if (xs.size() != 4 ) {
            return nullptr;
        } else {
            return std::make_unique<UptimeRequirement>( xs[1], xs[2], xs[3]);
        }
    };

    void check(sonar::ServerStatus &status) {
    };

    virtual std::string desc() {
        std::ostringstream ret;
        ret <<"UptimeRequirement(" << getId()  << "," << startTime << "," << endTime << ")";
        return ret.str();
    };
};

class LastNewsRequirement : public Rule {
 public:
 LastNewsRequirement(std::string s) : Rule(s) {};
    static RulePtr parse( std::vector<std::string> xs) {
        return std::make_unique<LastNewsRequirement>("woot2");
    };
    
    void check(sonar::ServerStatus &status) {
    };

    virtual std::string desc() {
        return "LastNewsRequirement";
    };
};
