#include <null-mono.h>

namespace mono {
	property_t* property_t::parse(const std::string& path) {
		if(!cached[path]) {
			parser_t parser{ path };
			cached[path] = assembly_t::open(parser.assembly)->image()->class_from_name(parser.name_space, parser.klass)->find_property(parser.member);
		}
		return cached[path];
	}

	const char* property_t::name() {
		return mono.property_get_name(this);
	}

	method_t* property_t::getter() {
		return mono.property_get_get_method(this);
	}

	method_t* property_t::setter() {
		return mono.property_get_set_method(this);
	}
}