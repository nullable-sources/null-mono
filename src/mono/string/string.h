#pragma once
#include <mono/exports.h>

namespace mono {
	struct string_t {
	public:
		static string_t* create(std::string_view str);
		static string_t* create(std::wstring_view str);

		std::string to_utf8();
		std::wstring to_utf16();

	public:
		operator std::string() { return to_utf8(); }
		operator std::wstring() { return to_utf16(); }
	};
}