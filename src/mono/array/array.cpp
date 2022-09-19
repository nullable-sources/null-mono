#include <null-mono.h>

namespace mono {
	array_t* array_t::create(class_t* klass, std::uintptr_t n) {
		return mono.array_new(domain_t::root(), klass, n);
	}

	array_t* array_t::copy() {
		return mono.array_clone(this);
	}

	std::uintptr_t array_t::length() {
		return mono.array_length(this);
	}

	memory::address_t array_t::addr_with_size(int size, std::uintptr_t idx) {
		return memory::address_t{ mono.array_addr_with_size(this, size, idx) };
	}
}