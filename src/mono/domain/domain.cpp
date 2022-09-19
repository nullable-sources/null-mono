#include <null-mono.h>

namespace mono {
	domain_t* domain_t::by_id(int id) {
		return mono.domain_get_by_id(id);
	}

	domain_t* domain_t::current() {
		return mono.domain_get();
	}

	domain_t* domain_t::root() {
		return mono.get_root_domain();
	}

	void domain_t::foreach(void(*func)(domain_t*, void*), void* user_data) {
		mono.domain_foreach(func, user_data);
	}

	assembly_t* domain_t::open_assembly(std::string_view name, e_assembly_open_flags flags) {
		return mono.domain_assembly_open(this, flags & e_assembly_open_flags::from_root_dir ? std::format("{}\\{}", assembly_t::root_dir(), name).c_str() : name.data());
	}

	std::uint32_t domain_t::set(std::uint32_t force) {
		return mono.domain_set(this, force);
	}

	std::uint32_t domain_t::id() {
		return mono.domain_get_id(this);
	}
}