#include <null-mono.h>

namespace mono {
	const char* assembly_name_t::name() {
		return mono.assembly_name_get_name(this);
	}

	const char* assembly_name_t::culture() {
		return mono.assembly_name_get_culture(this);
	}

	std::uint16_t assembly_name_t::minor() {
		std::uint16_t result{ };
		mono.assembly_name_get_version(this, &result, nullptr, nullptr);
		return result;
	}

	std::uint16_t assembly_name_t::build() {
		std::uint16_t result{ };
		mono.assembly_name_get_version(this, nullptr, &result, nullptr);
		return result;
	}

	std::uint16_t assembly_name_t::revision() {
		std::uint16_t result{ };
		mono.assembly_name_get_version(this, nullptr, nullptr, &result);
		return result;
	}

	std::uint16_t assembly_name_t::major() {
		return mono.assembly_name_get_version(this, nullptr, nullptr, nullptr);
	}

	const char* assembly_t::root_dir() {
		return mono.assembly_getrootdir();
	}

	assembly_t* assembly_t::main() {
		return mono.assembly_get_main();
	}

	assembly_t* assembly_t::open(const std::string& name, e_assembly_open_flags flags) {
		if(!cached[name]) cached[name] = domain_t::root()->open_assembly(name, flags);
		return cached[name];
	}

	assembly_name_t* assembly_t::assembly_name() {
		return mono.assembly_get_name(this);
	}

	image_t* assembly_t::image() {
		return mono.assembly_get_image(this);
	}

	class_t* assembly_t::find_class(std::string class_path) {
		parser_t parser{ class_path };
		return image()->class_from_name(parser.name_space.c_str(), parser.klass.c_str());
	}

	class_t* assembly_t::find_class(std::uint32_t token) {
		return image()->class_from_token(token);
	}

	assembly_t* image_t::assembly() {
		return mono.image_get_assembly(this);
	}

	const table_info_t* image_t::table_info(e_meta_table table_id) {
		return mono.image_get_table_info(this, table_id);
	}

	const char* image_t::name() {
		return mono.image_get_name(this);
	}

	class_t* image_t::class_from_name(std::string_view namespace_path, std::string_view class_path) {
		return mono.class_from_name(this, namespace_path.data(), class_path.data());
	}

	class_t* image_t::class_from_token(std::uint32_t token) {
		return mono.class_get(this, token);
	}

	int table_info_t::rows() const {
		return mono.table_info_get_rows(this);
	}
}