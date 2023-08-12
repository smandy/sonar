#include "timeUtils.h"
#include "boost/date_time/posix_time/posix_time.hpp"

namespace bam
{
bp::time_duration parseTime(std::string s)
{
    std::vector<std::string> tokens;
    boost::split(tokens, s, boost::is_any_of(":"));
    if (tokens.size() != 3) {
        std::ostringstream oss;
        oss << "Couldn't parse String : " << s;
        throw std::invalid_argument(oss.str());
    };
    return bp::hours(std::atoi(tokens[0].c_str())) +
           bp::minutes(std::atoi(tokens[1].c_str())) +
           bp::seconds(std::atoi(tokens[2].c_str()));
};

bp::ptime parseTimeToday(std::string s)
{
    bg::date d = bg::day_clock::local_day();
    return bp::ptime(d, parseTime(s));
};
} // namespace bam
