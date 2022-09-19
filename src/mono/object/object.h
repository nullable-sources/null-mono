#pragma once
#include <mono/exports.h>

namespace mono {
	struct object_t {
	public:
		static object_t* create(class_t* klass);

	public:
		class_t* parent_class();
		object_t* clone();

		void* unbox();

		int hash();

		string_t* to_string();
	};
}