#pragma once
#include <mono/exports.h>

namespace mono {
	struct array_t {
	public:
		static array_t* create(class_t* klass, std::uintptr_t n);

		template<typename element_t>
		static array_t* create(class_t* klass, const std::vector<element_t>& vector) {
			array_t* new_array{ create(klass, vector.size()) };
			for(int i : std::views::iota(0, (int)vector.size())) {
				*new_array->addr_with_size(sizeof(element_t), i).cast<element_t*>() = vector[i];
			}
			return new_array;
		}

	public:
		array_t* copy();

		std::uintptr_t length();
		memory::address_t addr_with_size(int size, std::uintptr_t idx);
	};
}