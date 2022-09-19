#pragma once
#include <mono/exports.h>

namespace mono {
	enum class e_thread_info_flags {
		mone,
		no_gc = 1 << 0,
		no_sample = 1 << 1
	}; enum_create_bit_operators(e_thread_info_flags, true);
	enum_create_cast_operator(e_thread_info_flags, -);

	enum class e_set_thread_name_flags {
		none,
		permanent = 1 << 0,
		reset = 1 << 1,
		constant = 1 << 2,
		repeatedly_but_optimized = 1 << 3,
	}; enum_create_bit_operators(e_set_thread_name_flags, true);
	enum_create_cast_operator(e_set_thread_name_flags, -);

	struct thread_t {
	public:
		static thread_t* attach();
		void detach();
	};
}