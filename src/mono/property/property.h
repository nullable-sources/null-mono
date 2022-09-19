#pragma once
#include <mono/exports.h>

namespace mono {
	struct property_t {
	private:
		static inline std::map<std::string, property_t*> cached{ };

	public:
		static property_t* parse(const std::string& path);

	public:
		const char* name();
		
		method_t* getter();
		method_t* setter();

		template<typename... args_t>
		object_t* get_instance(object_t* object, args_t&&... args) {
			return mono.property_get_value(this, object, std::vector<void*> { std::addressof(args)... }.data(), nullptr);
		}

		template<typename... args_t>
		object_t* get_static(args_t... args) {
			return get_instance(nullptr, args...);
		}

		template<typename... args_t>
		void set_instance(object_t* object, args_t&&... args) {
			return mono.property_set_value(this, object, std::vector<void*> { std::addressof(args)... }.data(), nullptr);
		}

		template<typename... args_t>
		void set_static(args_t... args) {
			set_instance(nullptr, args...);
		}
	};
}