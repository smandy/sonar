#pragma once

#include "rule.h"
#include <memory>
#include <ostream>
#include "boost/date_time/posix_time/posix_time.hpp"
#include "timeUtils.h"

namespace bp = boost::posix_time;
namespace bg = boost::gregorian;

class UptimeRequirement : public Rule {
    bp::ptime startTime;
    bp::ptime endTime;
 public:
    static RulePtr parse( std::vector<std::string> xs);
    
    UptimeRequirement(const std::string& s,
                   const std::string& st,
                   const std::string et);
    
    virtual void check(sonar::ServerStatus &status);
    
    virtual std::string desc();
};

