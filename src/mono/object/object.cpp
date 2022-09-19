#include <null-mono.h>

namespace mono {
	object_t* object_t::create(class_t* klass) {
		return mono.object_new(domain_t::root(), klass);
	}

	class_t* object_t::parent_class() {
		return mono.object_get_class(this);
	}

	object_t* object_t::clone() {
		return mono.object_clone(this);
	}

	void* object_t::unbox() {
		return mono.object_unbox(this);
	}

	int object_t::hash() {
		return mono.object_hash(this);
	}

	string_t* object_t::to_string() {
		return mono.object_to_string(this, nullptr);
	}
}