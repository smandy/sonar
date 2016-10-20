#pragma once

#include <vector>
#include "rule.h"
#include <fstream>

#include <boost/algorithm/string.hpp>
#include "prettyPrint.h"
#include <map>
#include "uptimeRequirement.h"
#include "lastNewsRequirement.h"
#include <functional>
#include <boost/filesystem.hpp>

namespace bfs = boost::filesystem;

static std::map<std::string,
    const std::function<RulePtr(std::vector<std::string>)> > dispatch  {
    { "upTime", UptimeRequirement::parse },
        { "lastNews", LastNewsRequirement::parse } };

class RuleLoader {
 public:
    static std::vector<RulePtr> parseRules(const std::string &fn);
};
