#include <null-mono.h>

namespace mono {
	method_t* method_t::parse(const std::string& path, int args_count) {
		if(!cached[{ path, args_count }]) {
			parser_t parser{ path };
			cached[{ path, args_count }] = assembly_t::open(parser.assembly)->image()->class_from_name(parser.name_space, parser.klass)->find_method(parser.member, args_count);
		}
		return cached[{ path, args_count }];
	}

	class_t* method_t::parent_class() {
		return mono.method_get_class(this);
	}

	const char* method_t::name() {
		return mono.method_get_name(this);
	}

	memory::address_t method_t::address() {
		return memory::address_t{ mono.compile_method(this) };
	};

	method_desc_t* method_desc_t::create(std::string_view signature) {
		return mono.method_desc_new(signature.data(), signature.contains('.'));
	}

	void method_desc_t::destroy() {
		mono.method_desc_free(this);
	}

	method_t* method_desc_t::search_in_class(class_t* klass) {
		if(!klass) throw std::runtime_error("klass empty");
		return mono.method_desc_search_in_class(this, klass);
	}

	method_t* method_desc_t::search_in_image(image_t* image) {
		if(!image) throw std::runtime_error("image empty");
		return mono.method_desc_search_in_image(this, image);
	}
}