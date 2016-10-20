#include "rule.h"
#include <memory>
#include <ostream>
#include "boost/date_time/posix_time/posix_time.hpp"

namespace bp = boost::posix_time;
namespace bg = boost::gregorian;

bp::time_duration parseTime( std::string s) {
    std::vector<std::string> tokens;
    boost::split(tokens, s, boost::is_any_of(":"));
    if (tokens.size() != 3 ) {
        std::ostringstream oss;
        oss << "Couldn't parse String : " << s;
        throw std::invalid_argument(oss.str());
    };
    return bp::hours( std::atoi( tokens[0].c_str()) ) +
        bp::minutes( std::atoi( tokens[1].c_str()) ) +
        bp::seconds( std::atoi( tokens[2].c_str()) );
};

bp::ptime parseTimeToday( std::string s) {
    bg::date d = bg::day_clock::local_day();
    return bp::ptime( d, parseTime(s) );
};

class UptimeRequirement : public Rule {
    bp::ptime startTime;
    bp::ptime endTime;
 public:
 UptimeRequirement(const std::string& s,
                   const std::string& st,
                   const std::string et) :
    Rule {s},
        startTime( parseTimeToday(st) ),
            endTime(parseTimeToday(et) ) {
            if (st>et) {
                std::ostringstream oss;
                oss << "Invalid range (st>et) : [" << st << "-" << st << "]";
                throw std::invalid_argument( oss.str());
            };
        };
    static RulePtr parse( std::vector<std::string> xs) {
        if (xs.size() != 4) {
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
