#include <null-mono.h>

namespace mono {
	field_t* field_t::parse(const std::string& path) {
		if(!cached[path]) {
			parser_t parser{ path };
			cached[path] = assembly_t::open(parser.assembly)->image()->class_from_name(parser.name_space, parser.klass)->find_field(parser.member);
		}
		return cached[path];
	}

	class_t* field_t::parent_class() {
		return mono.field_get_parent(this);
	}

	const char* field_t::name() {
		return mono.field_get_name(this);
	}

	std::intptr_t field_t::offset() {
		return mono.field_get_offset(this);
	}

	memory::address_t field_t::address(object_t* object) {
		if(object) return memory::address_t{ (std::uintptr_t)object }.offset(offset());
		return parent_class()->vtable()->static_fields_address().offset(offset());
	}
}