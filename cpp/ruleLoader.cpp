#include "ruleLoader.h"

std::vector<RulePtr> RuleLoader::parseRules(const std::string& fn)
{
    bfs::path p(fn);

    if (!bfs::is_regular_file(p)) {
        std::ostringstream oss;
        oss << "Bad filename : " << fn;
        throw std::invalid_argument(oss.str());
    };

    std::vector<RulePtr> ret{};
    std::ifstream is(fn);
    std::array<char, 128> buf;
    while (is.getline(&buf[0], buf.size())) {
        std::vector<std::string> tokens{"Tokens="};
        std::string s(&buf[0]);
        boost::split(tokens, s, boost::is_any_of(" "), boost::token_compress_on);
        if (s[0] == '#') {
            continue;
        };
        if (s.length() < 2) {
            continue;
        };
        auto it = dispatch.find(tokens[0]);
        if (it != end(dispatch)) {
            // std::cout << "Woot match on " << tokens[0] << std::endl;
            auto optCandidate = it->second(tokens);
            if (optCandidate) {
                ret.push_back(std::move(optCandidate));
            } else {
                std::cout << "Parser rejected input for " << tokens[0] << " : ";
                pp(std::cout, tokens);
            }
        } else {
            std::cout << "Warning - no parser for token " << tokens[0]
                      << " in non-trivial line : ";
            pp(std::cout, tokens);
        };
    };
    return ret;
}
