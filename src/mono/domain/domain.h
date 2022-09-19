#pragma once
#include <mono/exports.h>
#include <mono/assembly/assembly.h>

namespace mono {
	struct domain_t {
	public:
		static domain_t* by_id(int id);
		static domain_t* current();
		static domain_t* root();

		static void foreach(void(*func)(domain_t*, void*), void* user_data);

	public:
		assembly_t* open_assembly(std::string_view name, e_assembly_open_flags flags = e_assembly_open_flags::from_root_dir);

		std::uint32_t set(std::uint32_t force);
		std::uint32_t id();
	};
}