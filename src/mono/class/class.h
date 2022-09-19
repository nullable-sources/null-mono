#pragma once
#include <mono/exports.h>

template <typename sdk_type_t>
struct sdk_type_class_t {
	static mono::class_t* get() {
		return nullptr;
	}
};

namespace mono {
	struct class_t {
	private:
		static inline std::map<std::string, class_t*> cached{ };

	public:
		static class_t* parse(const std::string& path);

	public:
		type_t* type() { return mono.class_get_type(this); }

		const char* name();
		const char* name_space();

		vtable_t* vtable(domain_t* domain = nullptr);

		property_t* find_property(std::string_view name);
		field_t* find_field(std::string_view name);
		method_t* find_method(std::string_view name, int args_count = -1);

		property_t* properties(void* iterator);
	};

	struct vtable_t {
	public:
		domain_t* domain();
		memory::address_t static_fields_address();
	};
}