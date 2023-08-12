#include "uptimeRequirement.h"

UptimeRequirement::UptimeRequirement(const std::string& s,
                                     const std::string& st,
                                     const std::string et)
    : Rule{s}, startTime(bam::parseTimeToday(st)),
      endTime(bam::parseTimeToday(et))
{
    if (st > et) {
        std::ostringstream oss;
        oss << "Invalid range (st>et) : [" << st << "-" << st << "]";
        throw std::invalid_argument(oss.str());
    };
};

void UptimeRequirement::check(sonar::ServerStatus&){};

RulePtr UptimeRequirement::parse(std::vector<std::string> xs)
{
    if (xs.size() != 4) {
        return nullptr;
    } else {
        return std::make_unique<UptimeRequirement>(xs[1], xs[2], xs[3]);
    }
};

std::string UptimeRequirement::desc()
{
    std::ostringstream ret;
    ret << "UptimeRequirement(" << getId() << "," << startTime << "," << endTime
        << ")";
    return ret.str();
};
