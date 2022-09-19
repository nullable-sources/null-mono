#pragma once
#include <mono/exports.h>

namespace mono {
	struct method_t {
    private:
        static inline std::map<std::pair<std::string, int>, method_t*> cached{ };

    public:
        static method_t* parse(const std::string& path, int args_count = -1);

    public:
        template <typename> struct invoker_t;
        template <typename return_t, typename ...args_t>
        struct invoker_t<return_t(args_t...)> {
        public:
            return_t(*func)(args_t...){ };

        public:
            invoker_t(method_t* method) : func(method->address().cast<return_t(*)(args_t...)>()) { }

        public:
            return_t invoke(args_t... args) {
                if(!func) throw std::runtime_error{ "func empty" };
                return func(args...);
            }

            return_t operator ()(args_t... args) {
                return invoke(args...);
            }
        };

	public:
        class_t* parent_class();
        const char* name();
        memory::address_t address();

        template<typename ...args_t>
        object_t* invoke_instance(object_t* object, args_t&& ...args) {
            object_t* exception{ };
            object_t* result{ mono.runtime_invoke(this, object, std::vector<void*>{ std::addressof(args)... }.data(), &exception) };
            if(exception) throw std::runtime_error{ exception->to_string()->to_utf8() };
            return result;
        }

        template<typename ...args_t>
        object_t* invoke_static(args_t&& ...args) {
            return invoke_instance(nullptr, args...);
        }
	};

    struct method_desc_t {
    public:
        static method_desc_t* create(std::string_view signature);

    public:
        void destroy();

        method_t* search_in_class(class_t* klass);
        method_t* search_in_image(image_t* image);
    };
}