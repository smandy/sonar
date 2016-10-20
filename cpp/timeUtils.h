#pragma once

#include "boost/date_time/posix_time/posix_time.hpp"
#include <boost/algorithm/string.hpp>

namespace bp = boost::posix_time;
namespace bg = boost::gregorian;

namespace bam {
    bp::time_duration parseTime( std::string s);
    bp::ptime parseTimeToday( std::string s);
};
