#pragma once
#include <mono/exports.h>
#include <mono/class/class.h>
namespace mono {
	struct field_t {
	private:
		static inline std::map<std::string, field_t*> cached{ };

	public:
		static field_t* parse(const std::string& path);

	public:
		class_t* parent_class();
		const char* name();
		
		std::intptr_t offset();
		memory::address_t address(object_t* object = nullptr);
	};
}