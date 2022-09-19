#pragma once
#include <mono/exports.h>

//System::Collections::Generic::List<T>
namespace mscorlib::collections {
    template <typename element_t>
    class c_list : public mono::object_t {
    public:
        void add(const element_t& element) {
            static mono::method_t::invoker_t<void(c_list*, const element_t&)> invoker{ parent_class()->find_method("Add", 1) };
            invoker(this, element);
        }

        void clear() {
            static mono::method_t::invoker_t<void(c_list*)> invoker{ parent_class()->find_method(":Clear()") };
            invoker(this);
        }

        element_t get(int idx) {
            static mono::method_t::invoker_t<void(c_list*, int)> invoker{ parent_class()->find_property("Item")->getter() };
            return invoker(this, idx);
        }

        void set(int idx, const element_t& val) {
            static mono::method_t::invoker_t<void(c_list*, int, const element_t&)> invoker{ parent_class()->find_property("Item")->setter() };
            invoker(this, idx, val);
        }

        element_t* at(int idx) {
            static std::intptr_t offset{ parent_class()->find_field("_items")->offset() };
            return memory::address_t{ this }.offset(offset).deref().cast<mono::array_t*>()->addr_with_size(sizeof(element_t), idx);
        }

        int size() {
            static std::intptr_t offset{ parent_class()->find_field("_size")->offset() };
            return memory::address_t{ this }.offset(offset).deref();
        }
    };
}