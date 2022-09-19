#include <null-mono.h>

namespace mono {
	string_t* string_t::create(std::string_view str) {
		return mono.string_new(domain_t::root(), str.data());
	}

	string_t* string_t::create(std::wstring_view str) {
		return mono.string_new_utf16(domain_t::root(), str.data(), str.length());
	}

	std::string string_t::to_utf8() {
		char* utf8_str{ mono.string_to_utf8(this) };
		std::string result{ utf8_str };
		mono.free(utf8_str);
		return result;
	}

	std::wstring string_t::to_utf16() {
		return mono.string_chars(this);
	}
}