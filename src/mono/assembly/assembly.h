#pragma once
#include <mono/exports.h>

namespace mono {
	struct assembly_name_t {
	public:
		const char* name();
		const char* culture();

		std::uint16_t minor();
		std::uint16_t build();
		std::uint16_t revision();
		std::uint16_t major();
	};

	enum class e_assembly_open_flags {
		none,
		from_root_dir = 1 << 0
	}; enum_create_bit_operators(e_assembly_open_flags, true);
	enum_create_cast_operator(e_assembly_open_flags, -);

	struct assembly_t {
	private:
		static inline std::map<std::string, assembly_t*> cached{ };

	public:
		static const char* root_dir();
		static assembly_t* main();

		static assembly_t* open(const std::string& name, e_assembly_open_flags flags = e_assembly_open_flags::from_root_dir);

	public:
		assembly_name_t* assembly_name();
		image_t* image();

		class_t* find_class(std::string class_path);
		class_t* find_class(std::uint32_t token);
	};

	enum class e_meta_table {
		module,
		type_ref,
		type_def,
		field_pointer,
		field,
		method_pointer,
		method,
		param_pointer,
		param,
		interface_impl,
		member_ref, /* 0xA */
		constant,
		custom_attribute,
		field_marshal,
		decl_security,
		class_layout,
		field_layout, /* 0x10 */
		standalone_sig,
		event_map,
		event_pointer,
		event,
		property_map,
		property_pointer,
		property,
		method_semantics,
		method_impl,
		module_ref, /* 0x1A */
		type_spec,
		impl_map,
		field_rva,
		enc_log,
		enc_map,
		assembly, /* 0x20 */
		assembly_processor,
		assembly_os,
		assembly_ref,
		assembly_ref_processor,
		assembly_ref_os,
		file,
		exported_type,
		manifest_resource,
		nested_class,
		generic_param, /* 0x2A */
		method_spec,
		generic_param_constraint,
		unused8,
		unused9,
		unused10,

		/* portable PDB tables */
		document, /* 0x30 */
		method_body,
		local_scope,
		local_variable,
		local_constant,
		import_scope,
		state_machine_method,
		custom_debug_information
	};

	enum class e_token_type {
		module = 0x0 << 24,
		type_ref = 0x1 << 24,
		type_def = 0x2 << 24,
		field_def = 0x4 << 24,
		method_def = 0x6 << 24,
		param_def = 0x8 << 24,
		interface_impl = 0x9 << 24,
		member_ref = 0xA << 24,
		custom_attribute = 0xC << 24,
		permission = 0xE << 24,
		signature = 0x11 << 24,
		event = 0x14 << 24,
		property = 0x17 << 24,
		module_ref = 0x1A << 24,
		type_spec = 0x1B << 24,
		assembly = 0x20 << 24,
		assembly_ref = 0x23 << 24,
		file = 0x26 << 24,
		exported_type = 0x26 << 24,
		manifest_resource = 0x28 << 24,
		generic_param = 0x2A << 24,
		method_spec = 0x2B << 24,
		string = 0x70 << 24,
		name = 0x71 << 24,
		base_type = 0x72 << 24
	}; enum_create_bit_operators(e_token_type, true);
	enum_create_cast_operator(e_token_type, -);

	enum class e_image_open_status {
		ok,
		error_errno,
		missing_assembly_ref,
		image_invalid
	};

	struct image_t {
	public:
		assembly_t* assembly();
		const table_info_t* table_info(e_meta_table table_id);

		const char* name();

		class_t* class_from_name(std::string_view namespace_path, std::string_view class_path);
		class_t* class_from_token(std::uint32_t token);
	};

	struct table_info_t {
	public:
		int rows() const;
	};
}