#include <null-mono.h>

namespace mono {
	std::string type_t::name() {
		return mono.type_get_name(this);
	}
}