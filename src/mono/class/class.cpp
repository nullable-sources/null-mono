#include <null-mono.h>

namespace mono {
	class_t* class_t::parse(const std::string& path) {
		if(!cached[path]) {
			parser_t parser{ path };
			cached[path] = assembly_t::open(parser.assembly)->image()->class_from_name(parser.name_space, parser.klass);
		}
		return cached[path];
	}

	const char* class_t::name() {
		return mono.class_get_name(this);
	}

	const char* class_t::name_space() {
		return mono.class_get_namespace(this);
	}

	vtable_t* class_t::vtable(domain_t* domain) {
		return mono.class_vtable(domain ? domain : domain_t::current(), this);
	}

	property_t* class_t::find_property(std::string_view name) {
		return mono.class_get_property_from_name(this, name.data());
	}

	field_t* class_t::find_field(std::string_view name) {
		return mono.class_get_field_from_name(this, name.data());
	}

	method_t* class_t::find_method(std::string_view name, int args_count) {
		if(args_count == -1) {
			method_desc_t* desc{ method_desc_t::create(name) };
			if(!desc) throw std::runtime_error("desc empty");

			method_t* method{ desc->search_in_class(this) };
			if(!method) throw std::runtime_error("method empty");

			desc->destroy();
			return method;
		}
		return mono.class_get_method_from_name(this, name.data(), args_count);
	}

	property_t* class_t::properties(void* iterator) {
		return mono.class_get_properties(this, &iterator);
	}

	domain_t* vtable_t::domain() {
		return mono.vtable_domain(this);
	}

	memory::address_t vtable_t::static_fields_address() {
		return memory::address_t{ mono.vtable_get_static_field_data(this) };
	}
}