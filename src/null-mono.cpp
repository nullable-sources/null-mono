#include <null-mono.h>

namespace mono {
	parser_t::parser_t(std::string str) {
        std::erase(str, ' ');
        if(auto finded{ str.find_first_of("]") }; finded != std::string::npos) {
            assembly = str.substr(1, finded - 1);
            str.erase(str.begin(), std::next(str.begin(), finded + 1));
        }

        std::ranges::replace(str, '.', '/');
        std::ranges::replace(str, ':', '.');

        if(auto finded{ str.find("->") }; finded != std::string::npos) {
            member = str.substr(finded + 2);
            if(member.contains('(') && member.contains(')')) member.insert(member.begin(), ':');
            str.erase(finded);
        }

        if(auto finded{ str.find_last_of('.') }; finded != std::string::npos) {
            name_space = str.substr(0, finded);
            str.erase(str.begin(), std::next(str.begin(), finded + 1));
        }

        klass = str;
    }
}