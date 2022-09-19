#pragma once
#include <null-sdk.h>
#define mono_export(return_t, name, ...) c_export<return_t (__VA_ARGS__)> name { "mono-2.0-bdwgc.dll", std::format("mono_{}", #name) };

namespace mono {
	enum class e_meta_table;
	enum class e_image_open_status;
	enum class e_thread_info_flags;
	enum class e_set_thread_name_flags;

	struct dis_helper_t;

	struct app_context_t;
	struct generic_context_t;

	struct domain_t;
	struct app_domain_t;

	struct assembly_t;
	struct assembly_name_t;

	struct class_t;
	struct generic_param_t;

	struct vtable_t;

	struct field_t;
	struct reflection_field_t;

	struct image_t;
	struct table_info_t;

	struct method_t;
	struct method_desc_t;
	struct reflection_method_t;
	struct reflection_method_body_t;
	struct method_signature_t;
	struct method_header_t;
	struct generic_container_t;

	struct property_t;
	struct property_hash_t;
	struct reflection_property_t;

	struct thread_t;
	struct thread_info_t;
	struct internal_thread_t;
	struct native_thread_id_t;

	struct type_t;
	struct reflection_type_t;

	struct string_t;

	struct array_t;
	struct array_type_t;

	struct object_t;

	struct exception_t;

	struct error_t;

	enum class e_type_name_format {
		il,
		reflection,
		full_name,
		assembly_qualified
	};

	class c_mono_dll : public memory::c_module {
	public: using c_module::c_module;
		  mono_export(char*, disasm_code, dis_helper_t* dh, method_t* method, const std::uint8_t* ip, const std::uint8_t* end);

		  mono_export(const char*, get_machine_config);
		  mono_export(const char*, get_runtime_build_info);
		  mono_export(int, ee_api_version);
		  mono_export(void, set_assemblies_path, const char* path);
		  mono_export(void, set_config_dir, const char* dir);
		  mono_export(void, set_dirs, const char* assembly_dir, const char* config_dir);
		  mono_export(void, set_rootdir);
		  mono_export(char*, native_getrootdir);
		  mono_export(const char*, get_config_dir);
		  mono_export(image_t*, get_corlib);
		  mono_export(void, config_cleanup);
		  mono_export(const char*, config_get_cpu);
		  mono_export(const char*, config_get_os);
		  mono_export(std::int32_t, config_is_server_mode);
		  mono_export(void, config_parse, const char* filename);
		  mono_export(void, config_parse_memory, const char* buffer);
		  mono_export(void, config_set_server_mode, std::int32_t server_mode);
		  mono_export(const char*, config_string_for_assembly_file, const char* filename);


		  mono_export(void, object_describe, object_t* obj);
		  mono_export(void, object_describe_fields, object_t* obj);
		  mono_export(void, value_describe_fields, class_t* klass, const char* addr);
		  mono_export(void, class_describe_statics, class_t* klass);


		  //app context
		  mono_export(app_context_t*, context_get);
		  mono_export(char*, context_get_desc, generic_context_t* context);
		  mono_export(std::int32_t, context_get_domain_id, app_context_t* context);
		  mono_export(std::int32_t, context_get_id, app_context_t* context);
		  mono_export(void, context_init, domain_t* domain);
		  mono_export(void, context_set, app_context_t* new_context);


		  //domain
		  mono_export(void, domain_foreach, void (*func) (domain_t* domain, void* user_data), void* user_data);
		  mono_export(domain_t*, get_root_domain);
		  mono_export(void, domain_set_internal, domain_t* domain);
		  mono_export(std::int32_t, domain_set, domain_t* domain, std::int32_t force);
		  mono_export(domain_t*, domain_get);
		  mono_export(domain_t*, domain_get_by_id, std::int32_t domainid);
		  mono_export(domain_t*, domain_create_appdomain, char* friendly_name, char* configuration_file);
		  mono_export(domain_t*, domain_create);
		  mono_export(domain_t*, domain_from_appdomain, app_domain_t* appdomain);
		  mono_export(void, domain_free, domain_t* domain, std::int32_t force);
		  mono_export(void, domain_set_config, domain_t* domain, const char* base_dir, const char* config_file_name);
		  mono_export(assembly_t*, domain_assembly_open, domain_t* domain, const char* name);
		  mono_export(const char*, domain_get_friendly_name, domain_t* domain);
		  mono_export(std::int32_t, domain_get_id, domain_t* domain);
		  mono_export(std::int32_t, domain_finalize, domain_t* domain, std::uint32_t timeout);


		  //assembly
		  mono_export(void, assembly_foreach, void(assembly_t* assembly, void* user_data), void* user_data);
		  mono_export(assembly_t*, assembly_get_main);
		  mono_export(void, assembly_set_main, assembly_t* assembly);
		  mono_export(const char*, assembly_getrootdir);
		  mono_export(void, assembly_setrootdir, const char* root_dir);
		  mono_export(assembly_t*, assembly_open, const char* filename, e_image_open_status* status);
		  mono_export(void, assembly_close, assembly_t* assembly);
		  mono_export(std::uint32_t, assembly_addref, assembly_t* assembly);
		  mono_export(image_t*, assembly_get_image, assembly_t* assembly);
		  mono_export(image_t*, assembly_get_image_internal, assembly_t* assembly);
		  mono_export(assembly_name_t*, assembly_get_name, assembly_t* assembly);
		  mono_export(assembly_name_t*, assembly_get_name_internal, assembly_t* assembly);
		  mono_export(assembly_t*, assembly_load, assembly_name_t* aname, const char* basedir, e_image_open_status* status);
		  mono_export(assembly_t*, assembly_load_from, image_t* image, const char* fname, e_image_open_status* status);
		  mono_export(assembly_t*, assembly_load_with_partial_name, const char* name, e_image_open_status* status);
		  mono_export(assembly_t*, assembly_loaded, assembly_name_t* aname);
		  mono_export(image_t*, assembly_load_module, assembly_t* assembly, std::uint32_t idx);
		  mono_export(image_t*, assembly_load_module_checked, assembly_t* assembly, std::uint32_t idx, error_t* error);


		  //assembly name
		  mono_export(assembly_name_t*, assembly_name_new, const char* name);
		  mono_export(void, assembly_name_free, assembly_name_t* aname);
		  mono_export(bool, assembly_names_equal, assembly_name_t* l, assembly_name_t* r);
		  mono_export(bool, assembly_name_parse, const char* name, assembly_name_t* aname);
		  mono_export(const char*, assembly_name_get_culture, assembly_name_t* aname);
		  mono_export(const char*, assembly_name_get_name, assembly_name_t* aname);
		  mono_export(std::uint8_t*, assembly_name_get_pubkeytoken, assembly_name_t* aname);
		  mono_export(std::uint16_t, assembly_name_get_version, assembly_name_t* aname, std::uint16_t* minor, std::uint16_t* build, std::uint16_t* revision);
		  mono_export(char*, stringify_assembly_name, assembly_name_t* aname);


		  //class
		  mono_export(class_t*, class_from_generic_parameter, generic_param_t* param, image_t* image, std::int32_t is_mvar);
		  mono_export(class_t*, class_from_mono_type, type_t* type);
		  mono_export(class_t*, class_from_mono_type_internal, type_t* type);
		  mono_export(class_t*, class_from_name, image_t* image, const char* name_space, const char* name);
		  mono_export(class_t*, class_from_name_case, image_t* image, const char* name_space, const char* name);
		  mono_export(class_t*, class_from_typeref, image_t* image, std::uint32_t type_token);
		  mono_export(class_t*, class_from_typeref_checked, image_t* image, std::uint32_t type_token, error_t* error);
		  mono_export(class_t*, class_get, image_t* image, std::uint32_t type_token);
		  mono_export(class_t*, class_get_checked, image_t* image, std::uint32_t type_token, error_t* error);
		  mono_export(std::int32_t, class_init, class_t* klass);
		  mono_export(class_t*, class_get_full, image_t* image, std::uint32_t type_token, generic_context_t* context);
		  mono_export(vtable_t*, class_vtable, domain_t* domain, class_t* klass);
		  mono_export(generic_context_t*, class_get_context, class_t* klass);
		  mono_export(class_t*, class_get_element_class, class_t* klass);
		  mono_export(type_t*, class_get_type, class_t* klass);
		  mono_export(type_t*, class_enum_basetype, class_t* klass);
		  mono_export(type_t*, class_get_byref_type, class_t* klass);
		  mono_export(std::int32_t, class_array_element_size, class_t* klass);
		  mono_export(std::int32_t, class_value_size, class_t* klass, std::uint32_t* align);
		  mono_export(std::int32_t, class_data_size, class_t* klass);
		  mono_export(std::uint32_t, class_get_field_token, field_t* field);
		  mono_export(std::uint32_t, class_get_flags, class_t* klass);
		  mono_export(image_t*, class_get_image, class_t* klass);
		  mono_export(class_t*, class_get_interfaces, class_t* klass, void** iter);
		  mono_export(const char*, class_get_name, class_t* klass);
		  mono_export(const char*, class_get_namespace, class_t* klass);
		  mono_export(class_t*, class_get_nested_types, class_t* klass, void** iter);
		  mono_export(class_t*, class_get_nesting_type, class_t* klass);
		  mono_export(class_t*, class_get_nullable_param, class_t* klass);
		  mono_export(class_t*, class_get_parent, class_t* klass);
		  mono_export(int, class_get_rank, class_t* klass);
		  mono_export(std::uint32_t, class_get_type_token, class_t* klass);
		  mono_export(std::int32_t, class_implements_interface, class_t* klass, class_t* iface);
		  mono_export(method_t*, class_inflate_generic_method, method_t* method, generic_context_t* context);
		  mono_export(type_t*, class_inflate_generic_type, type_t* type, generic_context_t* context);
		  mono_export(std::int32_t, class_instance_size, class_t* klass);
		  mono_export(int, class_interface_offset, class_t* klass, class_t* itf);
		  mono_export(std::int32_t, class_min_align, class_t* klass);
		  mono_export(const char*, class_name_from_token, image_t* image, std::uint32_t type_token);
		  mono_export(field_t*, class_get_field, class_t* klass, std::uint32_t field_token);
		  mono_export(field_t*, class_get_field_from_name, class_t* klass, const char* name);
		  mono_export(field_t*, class_get_fields, class_t* klass, void** iter);
		  mono_export(int, class_num_fields, class_t* klass);
		  mono_export(method_t*, get_method, image_t* image, std::uint32_t token, class_t* klass);
		  mono_export(method_t*, class_get_method_from_name, class_t* klass, const char* name, int param_count);
		  mono_export(method_t*, class_get_method_from_name_flags, class_t* klass, const char* name, int param_count, int flags);
		  mono_export(method_t*, class_get_methods, class_t* klass, void** iter);
		  mono_export(int, class_num_methods, class_t* klass);
		  mono_export(property_t*, class_get_property_from_name, class_t* klass, const char* name);
		  mono_export(std::uint32_t, class_get_property_token, property_t* prop);
		  mono_export(property_t*, class_get_properties, class_t* klass, void** iter);
		  mono_export(int, class_num_properties, class_t* klass);
		  mono_export(std::int32_t, class_is_assignable_from, class_t* klass, class_t* oklass);
		  mono_export(std::int32_t, class_is_delegate, class_t* klass);
		  mono_export(std::int32_t, class_is_enum, class_t* klass);
		  mono_export(std::int32_t, class_is_nullable, class_t* klass);
		  mono_export(std::int32_t, class_is_subclass_of, class_t* klass, class_t* klassc, std::int32_t check_interfaces);
		  mono_export(std::int32_t, class_is_valid_enum, class_t* klass);
		  mono_export(std::int32_t, class_is_valuetype, class_t* klass);


		  //vtable
		  mono_export(class_t*, vtable_class, vtable_t* vtable);
		  mono_export(class_t*, vtable_class_internal, vtable_t* vtable);
		  mono_export(domain_t*, vtable_domain, vtable_t* vtable);
		  mono_export(domain_t*, vtable_domain_internal, vtable_t* vtable);
		  mono_export(std::uintptr_t, vtable_get_static_field_data, vtable_t* vt);


		  //field
		  mono_export(field_t*, field_from_token, image_t* image, std::uint32_t token, class_t** retklass, generic_context_t* context);
		  mono_export(char*, field_full_name, field_t* field);
		  mono_export(const char*, field_get_data, field_t* field);
		  mono_export(std::uint32_t, field_get_flags, field_t* field);
		  mono_export(const char*, field_get_name, field_t* field);
		  mono_export(reflection_field_t*, field_get_object, domain_t* domain, class_t* klass, field_t* field);
		  mono_export(std::uint32_t, field_get_offset, field_t* field);
		  mono_export(class_t*, field_get_parent, field_t* field);
		  mono_export(type_t*, field_get_type, field_t* field);
		  mono_export(object_t*, field_get_value_object, domain_t* domain, field_t* field, object_t* obj);
		  mono_export(void, field_get_value, object_t* obj, field_t* field, void* value);
		  mono_export(void, field_set_value, object_t* obj, field_t* field, void* value);
		  mono_export(void, field_static_get_value, vtable_t* vt, field_t* field, void* value);
		  mono_export(void, field_static_set_value, vtable_t* vt, field_t* field, void* value);


		  //image
		  mono_export(void, images_init);
		  mono_export(void, images_cleanup);
		  mono_export(void, image_init, image_t* image);
		  mono_export(void, image_init_name_cache, image_t* image);
		  mono_export(image_t*, image_open, const char* fname, e_image_open_status* status);
		  mono_export(void, image_close, image_t* image);
		  mono_export(assembly_t*, image_get_assembly, image_t* image);
		  mono_export(std::uint32_t, image_get_entry_point, image_t* image);
		  mono_export(const char*, image_get_filename, image_t* image);
		  mono_export(const char*, image_get_guid, image_t* image);
		  mono_export(const char*, image_get_name, image_t* image);
		  mono_export(const char*, image_get_strong_name, image_t* image, std::uint32_t* size);
		  mono_export(const table_info_t*, image_get_table_info, image_t* image, e_meta_table table_id);
		  mono_export(std::int32_t, image_is_dynamic, image_t* image);
		  mono_export(void*, image_lookup_resource, image_t* image, std::uint32_t res_id, std::uint32_t lang_id, wchar_t* name);
		  mono_export(void, image_add_to_name_cache, image_t* image, const char* nspace, const char* name, uint32_t idx);
		  mono_export(void, image_addref, image_t* image);
		  mono_export(int, table_info_get_rows, const table_info_t* table);
		  mono_export(int, image_get_table_rows, image_t* image, int table_id);
		  mono_export(image_t*, image_loaded, const char* name);
		  mono_export(image_t*, image_load_file_for_image, image_t* image, int fileidx);
		  mono_export(image_t*, image_load_module, image_t* image, int idx);


		  //method
		  mono_export(method_t*, method_get_last_managed);
		  mono_export(const char*, method_get_name, method_t* method);
		  mono_export(char*, method_get_full_name, method_t* method);
		  mono_export(char*, method_full_name, method_t* method, std::int32_t signature);
		  mono_export(reflection_method_body_t*, method_body_get_object, domain_t* domain, method_t* method);
		  mono_export(class_t*, method_get_class, method_t* method);
		  mono_export(generic_context_t*, method_get_context, method_t* method);
		  mono_export(std::uint32_t, method_get_flags, method_t* method, std::uint32_t* iflags);
		  mono_export(generic_container_t*, method_get_generic_container, method_t* method);
		  mono_export(std::uint32_t, method_get_index, method_t* method);
		  mono_export(reflection_method_t*, method_get_object, domain_t* domain, method_t* method, class_t* refclass);
		  mono_export(void, method_get_param_names, method_t* method, const char** names);
		  mono_export(std::uint32_t, method_get_param_token, method_t* method, int idx);
		  mono_export(std::uint32_t, method_get_token, method_t* method);
		  mono_export(char*, method_get_reflection_name, method_t* method);
		  mono_export(method_header_t*, method_get_header, method_t* method);
		  mono_export(method_header_t*, method_get_header_checked, method_t* method, error_t* error);
		  mono_export(const std::uint8_t*, method_header_get_code, method_header_t* header, std::uint32_t* code_size, std::uint32_t* max_stack);
		  mono_export(type_t**, method_header_get_locals, method_header_t* header, std::uint32_t* num_locals, std::int32_t* init_locals);
		  mono_export(int, method_header_get_num_clauses, method_header_t* header);
		  mono_export(method_signature_t*, method_get_signature, method_t* method, image_t* image, std::uint32_t token);
		  mono_export(method_signature_t*, method_get_signature_full, method_t* method, image_t* image, std::uint32_t token, generic_context_t* context);
		  mono_export(method_signature_t*, method_signature, method_t* method);
		  mono_export(method_signature_t*, method_signature_checked_slow, method_t* m, error_t* err);
		  mono_export(method_signature_t*, method_signature_internal_slow, method_t* m);
		  mono_export(method_desc_t*, method_desc_from_method, method_t* method);
		  mono_export(method_desc_t*, method_desc_new, const char* name, std::int32_t include_namespace);
		  mono_export(void, method_desc_free, method_desc_t* desc);
		  mono_export(std::int32_t, method_desc_full_match, method_desc_t* desc, method_t* method);
		  mono_export(std::int32_t, method_desc_is_full, method_desc_t* desc);
		  mono_export(std::int32_t, method_desc_match, method_desc_t* desc, method_t* method);
		  mono_export(method_t*, method_desc_search_in_class, method_desc_t* desc, class_t* klass);
		  mono_export(method_t*, method_desc_search_in_image, method_desc_t* desc, image_t* image);
		  mono_export(std::uintptr_t, compile_method, method_t* method);
		  mono_export(std::int32_t, method_can_access_field, method_t* method, field_t* field);
		  mono_export(std::int32_t, method_can_access_method, method_t* method, method_t* called);
		  mono_export(void, method_print_code, method_t* method);


		  //property
		  mono_export(const char*, property_get_name, property_t* prop);
		  mono_export(uint32_t, property_get_flags, property_t* prop);
		  mono_export(reflection_property_t*, property_get_object, domain_t* domain, class_t* klass, property_t* property);
		  mono_export(class_t*, property_get_parent, property_t* prop);
		  mono_export(method_t*, property_get_get_method, property_t* prop);
		  mono_export(method_t*, property_get_set_method, property_t* prop);
		  mono_export(object_t*, property_get_value, property_t* prop, void* obj, void** params, object_t** exc);
		  mono_export(void, property_set_value, property_t* prop, void* obj, void** params, object_t** exc);
		  mono_export(property_hash_t*, property_hash_new);
		  mono_export(void, property_hash_destroy, property_hash_t* hash);
		  mono_export(void, property_hash_insert, property_hash_t* hash, void* object, std::uint32_t property, void* value);
		  mono_export(void*, property_hash_lookup, property_hash_t* hash, void* object, std::uint32_t property);
		  mono_export(void, property_hash_remove_object, property_hash_t* hash, void* object);


		  //runtime
		  mono_export(void, runtime_init, domain_t* domain, void (*start_cb) (std::intptr_t tid, void* stack_start, void* func), void (*attach_cb) (std::intptr_t tid, void* stack_start));
		  mono_export(void, runtime_class_init, vtable_t* vtable);
		  mono_export(void, runtime_object_init, object_t* this_obj);
		  mono_export(void, runtime_quit);
		  mono_export(void, runtime_cleanup, domain_t* domain);
		  mono_export(int, runtime_exec_main, method_t* method, array_t* args, object_t** exc);
		  mono_export(void, runtime_exec_managed_code, domain_t* domain, void(*main_func)(void* user_data), void* main_args);
		  mono_export(object_t*, runtime_invoke, method_t* method, void* obj, void** params, object_t** exc);
		  mono_export(object_t*, runtime_try_invoke, method_t* method, void* obj, void** params, object_t** exc, error_t* error);
		  mono_export(object_t*, runtime_invoke_array, method_t* method, void* obj, array_t* params, object_t** exc);
		  mono_export(object_t*, runtime_delegate_invoke, object_t* delegate, void** params, object_t** exc);
		  mono_export(array_t*, runtime_get_main_args);
		  mono_export(std::int32_t, runtime_is_shutting_down);


		  //signature
		  mono_export(char*, signature_get_desc, method_signature_t* sig, std::int32_t include_namespace);
		  mono_export(std::int32_t, signature_explicit_this, method_signature_t* sig);
		  mono_export(char*, signature_full_name, method_signature_t* sig);
		  mono_export(uint32_t, signature_get_call_conv, method_signature_t* sig);
		  mono_export(type_t*, signature_get_params, method_signature_t* sig, void** iter);
		  mono_export(uint32_t, signature_get_param_count, method_signature_t* sig);
		  mono_export(type_t*, ignature_get_return_type, method_signature_t* sig);
		  mono_export(std::uint32_t, signature_hash, method_signature_t* sig);
		  mono_export(std::int32_t, signature_is_instance, method_signature_t* sig);
		  mono_export(std::int32_t, signature_param_is_out, method_signature_t* sig, int param_num);
		  mono_export(int, signature_vararg_start, method_signature_t* sig);
		  mono_export(void, stack_walk, std::int32_t(*func) (method_t* method, int32_t native_offset, int32_t il_offset, std::int32_t managed, void* data), void* user_data);
		  mono_export(void, stack_walk_no_il, std::int32_t(*func) (method_t* method, int32_t native_offset, int32_t il_offset, std::int32_t managed, void* data), void* user_data);


		  //thread
		  mono_export(thread_t*, thread_get_main);
		  mono_export(void, thread_set_main, thread_t* thread);
		  mono_export(internal_thread_t*, thread_internal_current);
		  mono_export(thread_t*, thread_current);
		  mono_export(void, thread_new_init, intptr_t tid, void* stack_start, void* func);
		  mono_export(void, thread_init, void (*start_cb) (std::intptr_t tid, void* stack_start, void* func), void (*attach_cb) (std::intptr_t tid, void* stack_start));
		  mono_export(void, thread_create, domain_t* domain, void* func, void* arg);
		  mono_export(thread_t*, thread_attach, domain_t* domain);
		  mono_export(thread_t*, thread_internal_attach, domain_t* domain);
		  mono_export(void, thread_detach, thread_t* thread);
		  mono_export(void, thread_internal_detach, thread_t* thread);
		  mono_export(std::int32_t, thread_detach_if_exiting);
		  mono_export(void, thread_cleanup);
		  mono_export(void, thread_stop, thread_t* thread);
		  mono_export(void, thread_exit);
		  mono_export(int32_t, thread_get_managed_id, thread_t* thread);
		  mono_export(char*, thread_get_name_utf8, thread_t* thread);
		  mono_export(exception_t*, thread_get_undeniable_exception);
		  mono_export(std::int32_t, thread_is_foreign, thread_t* thread);
		  mono_export(void, thread_set_name, internal_thread_t* thread, const char* name8, std::size_t name8_length, const wchar_t* name16, e_set_thread_name_flags flags, error_t* error);
		  mono_export(std::int32_t, native_thread_create, native_thread_id_t* tid, void* func, void* arg);
		  mono_export(std::int32_t, native_thread_join, native_thread_id_t tid);
		  mono_export(std::int32_t, native_thread_id_equals, native_thread_id_t id1, native_thread_id_t id2);
		  mono_export(native_thread_id_t, native_thread_id_get);
		  mono_export(void, native_thread_set_name, native_thread_id_t tid, const char* name);

		  //thread info
		  mono_export(thread_info_t*, thread_info_current_unchecked);
		  mono_export(thread_info_t*, thread_info_attach);
		  mono_export(void, thread_info_detach);
		  mono_export(e_thread_info_flags, thread_info_get_flags, thread_info_t* info);
		  mono_export(int, thread_info_get_small_id);
		  mono_export(void*, thread_info_get_tools_data);
		  mono_export(void, thread_info_install_interrupt, void (*callback) (void* data), void* data, std::int32_t* interrupted);
		  mono_export(int, thread_info_register_small_id);
		  mono_export(void, thread_info_set_flags, e_thread_info_flags flags);
		  mono_export(std::int32_t, thread_info_set_tools_data, void* data);
		  mono_export(void, thread_info_uninstall_interrupt, std::int32_t* interrupted);
		  mono_export(std::int32_t, thread_info_yield);


		  //type
		  mono_export(array_type_t*, type_get_array_type, type_t* type);
		  mono_export(class_t*, type_get_class, type_t* type);
		  mono_export(reflection_type_t*, type_get_object, domain_t* domain, type_t* type);
		  mono_export(class_t*, ptr_class_get, type_t* type);
		  mono_export(type_t*, type_get_ptr_type, type_t* type);
		  mono_export(type_t*, type_get_underlying_type, type_t* type);
		  mono_export(int, type_get_type, type_t* type);
		  mono_export(class_t*, type_get_modifiers, type_t* type, std::int32_t* is_required, void** iter);
		  mono_export(char*, type_get_name, type_t* type);
		  mono_export(char*, type_get_name_full, type_t* type, e_type_name_format format);
		  mono_export(method_signature_t*, type_get_signature, type_t* type);
		  mono_export(int, type_size, type_t* type, int* alignment);
		  mono_export(int, type_stack_size, type_t* type, int* alignment);
		  mono_export(std::int32_t, type_is_byref, type_t* type);
		  mono_export(std::int32_t, type_is_generic_parameter, type_t* type);
		  mono_export(std::int32_t, type_is_pointer, type_t* type);
		  mono_export(std::int32_t, type_is_primitive, type_t* type);
		  mono_export(std::int32_t, type_is_reference, type_t* type);
		  mono_export(std::int32_t, type_is_struct, type_t* type);
		  mono_export(std::int32_t, type_is_valid_enum_basetype, type_t* type);
		  mono_export(std::int32_t, type_is_void, type_t* type);


		  //string
		  mono_export(string_t*, string_new, domain_t* domain, const char* text);
		  mono_export(string_t*, string_new_checked, domain_t* domain, const char* text, error_t* merror);
		  mono_export(string_t*, string_new_len, domain_t* domain, const char* text, std::uint32_t length);
		  mono_export(string_t*, string_new_size, domain_t* domain, int32_t len);
		  mono_export(string_t*, string_new_utf16, domain_t* domain, const wchar_t* text, std::int32_t len);
		  mono_export(string_t*, string_new_utf32, domain_t* domain, const std::uint32_t* text, std::int32_t len);
		  mono_export(string_t*, string_new_wrapper, const char* text);
		  mono_export(string_t*, string_from_bstr, void* bstr);
		  mono_export(string_t*, string_from_utf16, wchar_t* data);
		  mono_export(string_t*, string_from_utf32, std::uint32_t* data);
		  mono_export(char*, string_to_utf8, string_t* string_obj);
		  mono_export(char*, string_to_utf8_checked, string_t* string_obj, error_t* error);
		  mono_export(wchar_t*, string_to_utf16, string_t* string_obj);
		  mono_export(std::uint32_t*, string_to_utf32, string_t* string_obj);
		  mono_export(wchar_t*, string_chars, string_t* s);
		  mono_export(string_t*, string_empty, domain_t* domain);
		  mono_export(string_t*, string_empty_wrapper);
		  mono_export(int, string_length, string_t* s);
		  mono_export(string_t*, string_intern, string_t* str);
		  mono_export(string_t*, string_is_interned, string_t* str);
		  mono_export(std::int32_t, string_equal, string_t* s1, string_t* s2);
		  mono_export(std::uint32_t, string_hash, string_t* s);
		  mono_export(wchar_t*, unicode_from_external, const char* in, std::size_t* bytes);
		  mono_export(char*, unicode_to_external, const wchar_t* uni);
		  mono_export(char*, utf8_from_external, const char* in);
		  mono_export(std::int32_t, utf8_validate_and_len, const char* source, long* oLength, const char** oEnd);
		  mono_export(std::int32_t, utf8_validate_and_len_with_bounds, const char* source, long max_bytes, long* oLength, const char** oEnd);


		  //array
		  mono_export(std::uintptr_t, array_addr_with_size, array_t* array, int size, uintptr_t idx);
		  mono_export(class_t*, array_class_get, class_t* eclass, std::uint32_t rank);
		  mono_export(array_t*, array_clone, array_t* array);
		  mono_export(std::uint32_t, array_element_size, class_t* ac);
		  mono_export(std::uintptr_t, array_length, array_t* array);
		  mono_export(array_t*, array_new, domain_t* domain, class_t* eclass, uintptr_t n);


		  //value
		  mono_export(object_t*, value_box, domain_t* domain, class_t* klass, void* val);
		  mono_export(void, value_copy, void* dest, void* src, class_t* klass);
		  mono_export(void, value_copy_array, array_t* dest, int dest_idx, void* src, int count);


		  //object
		  mono_export(object_t*, object_new, domain_t* domain, class_t* klass);
		  mono_export(object_t*, object_new_fast, vtable_t* vtable);
		  mono_export(object_t*, object_new_from_token, domain_t* domain, image_t* image, uint32_t token);
		  mono_export(object_t*, object_new_specific, vtable_t* vtable);
		  mono_export(object_t*, object_clone, object_t* obj);
		  mono_export(class_t*, object_get_class, object_t* obj);
		  mono_export(domain_t*, object_get_domain, object_t* obj);
		  mono_export(std::uint32_t, object_get_size, object_t* obj);
		  mono_export(std::uint32_t, object_get_size_internal, object_t* obj);
		  mono_export(method_t*, object_get_virtual_method, object_t* obj, method_t* method);
		  mono_export(vtable_t*, object_get_vtable, object_t* obj);
		  mono_export(vtable_t*, object_get_vtable_internal, object_t* obj);
		  mono_export(string_t*, object_to_string, object_t* obj, object_t** exc);
		  mono_export(void*, object_unbox, object_t* obj);
		  mono_export(object_t*, object_castclass_mbyref, object_t* obj, class_t* klass);
		  mono_export(int, object_hash, object_t* obj);


		  //error
		  mono_export(void, error_init, error_t* error);
		  mono_export(void, error_init_flags, error_t* error, unsigned short flags);
		  mono_export(void, error_cleanup, error_t* error);
		  mono_export(unsigned short, error_get_error_code, error_t* error);
		  mono_export(const char*, error_get_message, error_t* error);
		  mono_export(std::int32_t, error_ok, error_t* error);


		  //exception
		  mono_export(void, unhandled_exception, object_t* exc);
		  mono_export(exception_t*, exception_from_name, image_t* image, const char* name_space, const char* name);
		  mono_export(exception_t*, exception_from_name_domain, domain_t* domain, image_t* image, const char* name_space, const char* name);
		  mono_export(exception_t*, exception_from_name_msg, image_t* image, const char* name_space, const char* name, const char* msg);
		  mono_export(exception_t*, exception_from_name_two_strings, image_t* image, const char* name_space, const char* name, string_t* a1, string_t* a2);
		  mono_export(exception_t*, exception_from_token, image_t* image, uint32_t token);
		  mono_export(std::int32_t, exception_walk_trace, exception_t* ex, std::int32_t(*func) (method_t* method, void* ip, size_t native_offset, std::int32_t managed, void* user_data), void* user_data);
		  mono_export(exception_t*, get_exception_argument, const char* arg, const char* msg);
		  mono_export(exception_t*, get_exception_argument_null, const char* arg);
		  mono_export(exception_t*, get_exception_argument_out_of_range, const char* arg);
		  mono_export(exception_t*, get_exception_arithmetic);
		  mono_export(exception_t*, get_exception_array_type_mismatch);
		  mono_export(exception_t*, get_exception_bad_image_format, const char* arg);
		  mono_export(exception_t*, get_exception_bad_image_format2, const char* msg, string_t* fname);
		  mono_export(exception_t*, get_exception_cannot_unload_appdomain, const char* msg);
		  mono_export(exception_t*, get_exception_divide_by_zero);
		  mono_export(exception_t*, get_exception_execution_engine, const char* msg);
		  mono_export(exception_t*, get_exception_field_access);
		  mono_export(exception_t*, get_exception_file_not_found, string_t* fname);
		  mono_export(exception_t*, get_exception_file_not_found2, const char* msg, string_t* fname);
		  mono_export(exception_t*, get_exception_index_out_of_range);
		  mono_export(exception_t*, get_exception_invalid_cast);
		  mono_export(exception_t*, get_exception_invalid_operation, const char* msg);
		  mono_export(exception_t*, get_exception_io, const char* msg);
		  mono_export(exception_t*, get_exception_method_access);
		  mono_export(exception_t*, get_exception_missing_field, const char* class_name, const char* member_name);
		  mono_export(exception_t*, get_exception_missing_method, const char* class_name, const char* member_name);
		  mono_export(exception_t*, get_exception_not_implemented, const char* msg);
		  mono_export(exception_t*, get_exception_not_supported, const char* msg);
		  mono_export(exception_t*, get_exception_null_reference);
		  mono_export(exception_t*, get_exception_out_of_memory);
		  mono_export(exception_t*, get_exception_overflow);
		  mono_export(exception_t*, get_exception_reflection_type_load, array_t* types, array_t* exceptions);
		  mono_export(exception_t*, get_exception_runtime_wrapped, object_t* wrapped_exception);
		  mono_export(exception_t*, get_exception_security);
		  mono_export(exception_t*, get_exception_serialization, const char* msg);
		  mono_export(exception_t*, get_exception_stack_overflow);
		  mono_export(exception_t*, get_exception_synchronization_lock, const char* msg);
		  mono_export(exception_t*, get_exception_thread_abort);
		  mono_export(exception_t*, get_exception_thread_interrupted);
		  mono_export(exception_t*, get_exception_thread_state, const char* msg);
		  mono_export(exception_t*, get_exception_type_initialization, const char* type_name, exception_t* inner);
		  mono_export(exception_t*, get_exception_type_load, string_t* class_name, char* assembly_name);


		  mono_export(class_t*, get_exception_class);
		  mono_export(class_t*, get_double_class);
		  mono_export(class_t*, get_enum_class);
		  mono_export(class_t*, get_int16_class);
		  mono_export(class_t*, get_int32_class);
		  mono_export(class_t*, get_int64_class);
		  mono_export(class_t*, get_intptr_class);
		  mono_export(class_t*, get_object_class);
		  mono_export(class_t*, get_sbyte_class);
		  mono_export(class_t*, get_single_class);
		  mono_export(class_t*, get_string_class);
		  mono_export(class_t*, get_thread_class);
		  mono_export(class_t*, get_uint16_class);
		  mono_export(class_t*, get_uint32_class);
		  mono_export(class_t*, get_uint64_class);
		  mono_export(class_t*, get_uintptr_class);
		  mono_export(class_t*, get_void_class);
		  mono_export(class_t*, get_array_class);
		  mono_export(class_t*, get_boolean_class);
		  mono_export(class_t*, get_byte_class);
		  mono_export(class_t*, get_char_class);

		  mono_export(type_t*, reflection_type_from_name, const char* name, image_t* image);
		  mono_export(void, free, void*);
	} static inline mono{ "mono-2.0-bdwgc.dll" };

	//namespace exports {
	//	mono_export(char*, disasm_code, dis_helper_t* dh, method_t* method, const std::uint8_t* ip, const std::uint8_t* end);

	//	mono_export(const char*, get_machine_config);
	//	mono_export(const char*, get_runtime_build_info);
	//	mono_export(int, ee_api_version);
	//	mono_export(void, set_assemblies_path, const char* path);
	//	mono_export(void, set_config_dir, const char* dir);
	//	mono_export(void, set_dirs, const char* assembly_dir, const char* config_dir);
	//	mono_export(void, set_rootdir);
	//	mono_export(char*, native_getrootdir);
	//	mono_export(const char*, get_config_dir);
	//	mono_export(image_t*, get_corlib);
	//	mono_export(void, config_cleanup);
	//	mono_export(const char*, config_get_cpu);
	//	mono_export(const char*, config_get_os);
	//	mono_export(std::int32_t, config_is_server_mode);
	//	mono_export(void, config_parse, const char* filename);
	//	mono_export(void, config_parse_memory, const char* buffer);
	//	mono_export(void, config_set_server_mode, std::int32_t server_mode);
	//	mono_export(const char*, config_string_for_assembly_file, const char* filename);


	//	mono_export(void, object_describe, object_t* obj);
	//	mono_export(void, object_describe_fields, object_t* obj);
	//	mono_export(void, value_describe_fields, class_t* klass, const char* addr);
	//	mono_export(void, class_describe_statics, class_t* klass);


	//	//app context
	//	mono_export(app_context_t*, context_get);
	//	mono_export(char*, context_get_desc, generic_context_t* context);
	//	mono_export(std::int32_t, context_get_domain_id, app_context_t* context);
	//	mono_export(std::int32_t, context_get_id, app_context_t* context);
	//	mono_export(void, context_init, domain_t* domain);
	//	mono_export(void, context_set, app_context_t* new_context);


	//	//domain
	//	mono_export(void, domain_foreach, void (*func) (domain_t* domain, void* user_data), void* user_data);
	//	mono_export(domain_t*, get_root_domain);
	//	mono_export(void, domain_set_internal, domain_t* domain);
	//	mono_export(std::int32_t, domain_set, domain_t* domain, std::int32_t force);
	//	mono_export(domain_t*, domain_get);
	//	mono_export(domain_t*, domain_get_by_id, std::int32_t domainid);
	//	mono_export(domain_t*, domain_create_appdomain, char* friendly_name, char* configuration_file);
	//	mono_export(domain_t*, domain_create);
	//	mono_export(domain_t*, domain_from_appdomain, app_domain_t* appdomain);
	//	mono_export(void, domain_free, domain_t* domain, std::int32_t force);
	//	mono_export(void, domain_set_config, domain_t* domain, const char* base_dir, const char* config_file_name);
	//	mono_export(assembly_t*, domain_assembly_open, domain_t* domain, const char* name);
	//	mono_export(const char*, domain_get_friendly_name, domain_t* domain);
	//	mono_export(std::int32_t, domain_get_id, domain_t* domain);
	//	mono_export(std::int32_t, domain_finalize, domain_t* domain, std::uint32_t timeout);


	//	//assembly
	//	mono_export(void, assembly_foreach, void(assembly_t* assembly, void* user_data), void* user_data);
	//	mono_export(assembly_t*, assembly_get_main);
	//	mono_export(void, assembly_set_main, assembly_t* assembly);
	//	mono_export(const char*, assembly_getrootdir);
	//	mono_export(void, assembly_setrootdir, const char* root_dir);
	//	mono_export(assembly_t*, assembly_open, const char* filename, e_image_open_status* status);
	//	mono_export(void, assembly_close, assembly_t* assembly);
	//	mono_export(std::uint32_t, assembly_addref, assembly_t* assembly);
	//	mono_export(image_t*, assembly_get_image, assembly_t* assembly);
	//	mono_export(image_t*, assembly_get_image_internal, assembly_t* assembly);
	//	mono_export(assembly_name_t*, assembly_get_name, assembly_t* assembly);
	//	mono_export(assembly_name_t*, assembly_get_name_internal, assembly_t* assembly);
	//	mono_export(assembly_t*, assembly_load, assembly_name_t* aname, const char* basedir, e_image_open_status* status);
	//	mono_export(assembly_t*, assembly_load_from, image_t* image, const char* fname, e_image_open_status* status);
	//	mono_export(assembly_t*, assembly_load_with_partial_name, const char* name, e_image_open_status* status);
	//	mono_export(assembly_t*, assembly_loaded, assembly_name_t* aname);
	//	mono_export(image_t*, assembly_load_module, assembly_t* assembly, std::uint32_t idx);
	//	mono_export(image_t*, assembly_load_module_checked, assembly_t* assembly, std::uint32_t idx, error_t* error);


	//	//assembly name
	//	mono_export(assembly_name_t*, assembly_name_new, const char* name);
	//	mono_export(void, assembly_name_free, assembly_name_t* aname);
	//	mono_export(bool, assembly_names_equal, assembly_name_t* l, assembly_name_t* r);
	//	mono_export(bool, assembly_name_parse, const char* name, assembly_name_t* aname);
	//	mono_export(const char*, assembly_name_get_culture, assembly_name_t* aname);
	//	mono_export(const char*, assembly_name_get_name, assembly_name_t* aname);
	//	mono_export(std::uint8_t*, assembly_name_get_pubkeytoken, assembly_name_t* aname);
	//	mono_export(std::uint16_t, assembly_name_get_version, assembly_name_t* aname, std::uint16_t* minor, std::uint16_t* build, std::uint16_t* revision);
	//	mono_export(char*, stringify_assembly_name, assembly_name_t* aname);


	//	//class
	//	mono_export(class_t*, class_from_generic_parameter, generic_param_t* param, image_t* image, std::int32_t is_mvar);
	//	mono_export(class_t*, class_from_mono_type, type_t* type);
	//	mono_export(class_t*, class_from_mono_type_internal, type_t* type);
	//	mono_export(class_t*, class_from_name, image_t* image, const char* name_space, const char* name);
	//	mono_export(class_t*, class_from_name_case, image_t* image, const char* name_space, const char* name);
	//	mono_export(class_t*, class_from_typeref, image_t* image, std::uint32_t type_token);
	//	mono_export(class_t*, class_from_typeref_checked, image_t* image, std::uint32_t type_token, error_t* error);
	//	mono_export(class_t*, class_get, image_t* image, std::uint32_t type_token);
	//	mono_export(class_t*, class_get_checked, image_t* image, std::uint32_t type_token, error_t* error);
	//	mono_export(std::int32_t, class_init, class_t* klass);
	//	mono_export(class_t*, class_get_full, image_t* image, std::uint32_t type_token, generic_context_t* context);
	//	mono_export(vtable_t*, class_vtable, domain_t* domain, class_t* klass);
	//	mono_export(generic_context_t*, class_get_context, class_t* klass);
	//	mono_export(class_t*, class_get_element_class, class_t* klass);
	//	mono_export(type_t*, class_get_type, class_t* klass);
	//	mono_export(type_t*, class_enum_basetype, class_t* klass);
	//	mono_export(type_t*, class_get_byref_type, class_t* klass);
	//	mono_export(std::int32_t, class_array_element_size, class_t* klass);
	//	mono_export(std::int32_t, class_value_size, class_t* klass, std::uint32_t* align);
	//	mono_export(std::int32_t, class_data_size, class_t* klass);
	//	mono_export(std::uint32_t, class_get_field_token, field_t* field);
	//	mono_export(std::uint32_t, class_get_flags, class_t* klass);
	//	mono_export(image_t*, class_get_image, class_t* klass);
	//	mono_export(class_t*, class_get_interfaces, class_t* klass, void** iter);
	//	mono_export(const char*, class_get_name, class_t* klass);
	//	mono_export(const char*, class_get_namespace, class_t* klass);
	//	mono_export(class_t*, class_get_nested_types, class_t* klass, void** iter);
	//	mono_export(class_t*, class_get_nesting_type, class_t* klass);
	//	mono_export(class_t*, class_get_nullable_param, class_t* klass);
	//	mono_export(class_t*, class_get_parent, class_t* klass);
	//	mono_export(int, class_get_rank, class_t* klass);
	//	mono_export(std::uint32_t, class_get_type_token, class_t* klass);
	//	mono_export(std::int32_t, class_implements_interface, class_t* klass, class_t* iface);
	//	mono_export(method_t*, class_inflate_generic_method, method_t* method, generic_context_t* context);
	//	mono_export(type_t*, class_inflate_generic_type, type_t* type, generic_context_t* context);
	//	mono_export(std::int32_t, class_instance_size, class_t* klass);
	//	mono_export(int, class_interface_offset, class_t* klass, class_t* itf);
	//	mono_export(std::int32_t, class_min_align, class_t* klass);
	//	mono_export(const char*, class_name_from_token, image_t* image, std::uint32_t type_token);
	//	mono_export(field_t*, class_get_field, class_t* klass, std::uint32_t field_token);
	//	mono_export(field_t*, class_get_field_from_name, class_t* klass, const char* name);
	//	mono_export(field_t*, class_get_fields, class_t* klass, void** iter);
	//	mono_export(int, class_num_fields, class_t* klass);
	//	mono_export(method_t*, get_method, image_t* image, std::uint32_t token, class_t* klass);
	//	mono_export(method_t*, class_get_method_from_name, class_t* klass, const char* name, int param_count);
	//	mono_export(method_t*, class_get_method_from_name_flags, class_t* klass, const char* name, int param_count, int flags);
	//	mono_export(method_t*, class_get_methods, class_t* klass, void** iter);
	//	mono_export(int, class_num_methods, class_t* klass);
	//	mono_export(property_t*, class_get_property_from_name, class_t* klass, const char* name);
	//	mono_export(std::uint32_t, class_get_property_token, property_t* prop);
	//	mono_export(property_t*, class_get_properties, class_t* klass, void** iter);
	//	mono_export(int, class_num_properties, class_t* klass);
	//	mono_export(std::int32_t, class_is_assignable_from, class_t* klass, class_t* oklass);
	//	mono_export(std::int32_t, class_is_delegate, class_t* klass);
	//	mono_export(std::int32_t, class_is_enum, class_t* klass);
	//	mono_export(std::int32_t, class_is_nullable, class_t* klass);
	//	mono_export(std::int32_t, class_is_subclass_of, class_t* klass, class_t* klassc, std::int32_t check_interfaces);
	//	mono_export(std::int32_t, class_is_valid_enum, class_t* klass);
	//	mono_export(std::int32_t, class_is_valuetype, class_t* klass);


	//	//vtable
	//	mono_export(class_t*, vtable_class, vtable_t* vtable);
	//	mono_export(class_t*, vtable_class_internal, vtable_t* vtable);
	//	mono_export(domain_t*, vtable_domain, vtable_t* vtable);
	//	mono_export(domain_t*, vtable_domain_internal, vtable_t* vtable);
	//	mono_export(std::uintptr_t, vtable_get_static_field_data, vtable_t* vt);


	//	//field
	//	mono_export(field_t*, field_from_token, image_t* image, std::uint32_t token, class_t** retklass, generic_context_t* context);
	//	mono_export(char*, field_full_name, field_t* field);
	//	mono_export(const char*, field_get_data, field_t* field);
	//	mono_export(std::uint32_t, field_get_flags, field_t* field);
	//	mono_export(const char*, field_get_name, field_t* field);
	//	mono_export(reflection_field_t*, field_get_object, domain_t* domain, class_t* klass, field_t* field);
	//	mono_export(std::uint32_t, field_get_offset, field_t* field);
	//	mono_export(class_t*, field_get_parent, field_t* field);
	//	mono_export(type_t*, field_get_type, field_t* field);
	//	mono_export(object_t*, field_get_value_object, domain_t* domain, field_t* field, object_t* obj);
	//	mono_export(void, field_get_value, object_t* obj, field_t* field, void* value);
	//	mono_export(void, field_set_value, object_t* obj, field_t* field, void* value);
	//	mono_export(void, field_static_get_value, vtable_t* vt, field_t* field, void* value);
	//	mono_export(void, field_static_set_value, vtable_t* vt, field_t* field, void* value);


	//	//image
	//	mono_export(void, images_init);
	//	mono_export(void, images_cleanup);
	//	mono_export(void, image_init, image_t* image);
	//	mono_export(void, image_init_name_cache, image_t* image);
	//	mono_export(image_t*, image_open, const char* fname, e_image_open_status* status);
	//	mono_export(void, image_close, image_t* image);
	//	mono_export(assembly_t*, image_get_assembly, image_t* image);
	//	mono_export(std::uint32_t, image_get_entry_point, image_t* image);
	//	mono_export(const char*, image_get_filename, image_t* image);
	//	mono_export(const char*, image_get_guid, image_t* image);
	//	mono_export(const char*, image_get_name, image_t* image);
	//	mono_export(const char*, image_get_strong_name, image_t* image, std::uint32_t* size);
	//	mono_export(const table_info_t*, image_get_table_info, image_t* image, e_meta_table table_id);
	//	mono_export(std::int32_t, image_is_dynamic, image_t* image);
	//	mono_export(void*, image_lookup_resource, image_t* image, std::uint32_t res_id, std::uint32_t lang_id, wchar_t* name);
	//	mono_export(void, image_add_to_name_cache, image_t* image, const char* nspace, const char* name, uint32_t idx);
	//	mono_export(void, image_addref, image_t* image);
	//	mono_export(int, table_info_get_rows, const table_info_t* table);
	//	mono_export(int, image_get_table_rows, image_t* image, int table_id);
	//	mono_export(image_t*, image_loaded, const char* name);
	//	mono_export(image_t*, image_load_file_for_image, image_t* image, int fileidx);
	//	mono_export(image_t*, image_load_module, image_t* image, int idx);


	//	//method
	//	mono_export(method_t*, method_get_last_managed);
	//	mono_export(const char*, method_get_name, method_t* method);
	//	mono_export(char*, method_get_full_name, method_t* method);
	//	mono_export(char*, method_full_name, method_t* method, std::int32_t signature);
	//	mono_export(reflection_method_body_t*, method_body_get_object, domain_t* domain, method_t* method);
	//	mono_export(class_t*, method_get_class, method_t* method);
	//	mono_export(generic_context_t*, method_get_context, method_t* method);
	//	mono_export(std::uint32_t, method_get_flags, method_t* method, std::uint32_t* iflags);
	//	mono_export(generic_container_t*, method_get_generic_container, method_t* method);
	//	mono_export(std::uint32_t, method_get_index, method_t* method);
	//	mono_export(reflection_method_t*, method_get_object, domain_t* domain, method_t* method, class_t* refclass);
	//	mono_export(void, method_get_param_names, method_t* method, const char** names);
	//	mono_export(std::uint32_t, method_get_param_token, method_t* method, int idx);
	//	mono_export(std::uint32_t, method_get_token, method_t* method);
	//	mono_export(char*, method_get_reflection_name, method_t* method);
	//	mono_export(method_header_t*, method_get_header, method_t* method);
	//	mono_export(method_header_t*, method_get_header_checked, method_t* method, error_t* error);
	//	mono_export(const std::uint8_t*, method_header_get_code, method_header_t* header, std::uint32_t* code_size, std::uint32_t* max_stack);
	//	mono_export(type_t**, method_header_get_locals, method_header_t* header, std::uint32_t* num_locals, std::int32_t* init_locals);
	//	mono_export(int, method_header_get_num_clauses, method_header_t* header);
	//	mono_export(method_signature_t*, method_get_signature, method_t* method, image_t* image, std::uint32_t token);
	//	mono_export(method_signature_t*, method_get_signature_full, method_t* method, image_t* image, std::uint32_t token, generic_context_t* context);
	//	mono_export(method_signature_t*, method_signature, method_t* method);
	//	mono_export(method_signature_t*, method_signature_checked_slow, method_t* m, error_t* err);
	//	mono_export(method_signature_t*, method_signature_internal_slow, method_t* m);
	//	mono_export(method_desc_t*, method_desc_from_method, method_t* method);
	//	mono_export(method_desc_t*, method_desc_new, const char* name, std::int32_t include_namespace);
	//	mono_export(void, method_desc_free, method_desc_t* desc);
	//	mono_export(std::int32_t, method_desc_full_match, method_desc_t* desc, method_t* method);
	//	mono_export(std::int32_t, method_desc_is_full, method_desc_t* desc);
	//	mono_export(std::int32_t, method_desc_match, method_desc_t* desc, method_t* method);
	//	mono_export(method_t*, method_desc_search_in_class, method_desc_t* desc, class_t* klass);
	//	mono_export(method_t*, method_desc_search_in_image, method_desc_t* desc, image_t* image);
	//	mono_export(std::uintptr_t, compile_method, method_t* method);
	//	mono_export(std::int32_t, method_can_access_field, method_t* method, field_t* field);
	//	mono_export(std::int32_t, method_can_access_method, method_t* method, method_t* called);
	//	mono_export(void, method_print_code, method_t* method);


	//	//property
	//	mono_export(const char*, property_get_name, property_t* prop);
	//	mono_export(uint32_t, property_get_flags, property_t* prop);
	//	mono_export(reflection_property_t*, property_get_object, domain_t* domain, class_t* klass, property_t* property);
	//	mono_export(class_t*, property_get_parent, property_t* prop);
	//	mono_export(method_t*, property_get_get_method, property_t* prop);
	//	mono_export(method_t*, property_get_set_method, property_t* prop);
	//	mono_export(object_t*, property_get_value, property_t* prop, void* obj, void** params, object_t** exc);
	//	mono_export(void, property_set_value, property_t* prop, void* obj, void** params, object_t** exc);
	//	mono_export(property_hash_t*, property_hash_new);
	//	mono_export(void, property_hash_destroy, property_hash_t* hash);
	//	mono_export(void, property_hash_insert, property_hash_t* hash, void* object, std::uint32_t property, void* value);
	//	mono_export(void*, property_hash_lookup, property_hash_t* hash, void* object, std::uint32_t property);
	//	mono_export(void, property_hash_remove_object, property_hash_t* hash, void* object);


	//	//runtime
	//	mono_export(void, runtime_init, domain_t* domain, void (*start_cb) (std::intptr_t tid, void* stack_start, void* func), void (*attach_cb) (std::intptr_t tid, void* stack_start));
	//	mono_export(void, runtime_class_init, vtable_t* vtable);
	//	mono_export(void, runtime_object_init, object_t* this_obj);
	//	mono_export(void, runtime_quit);
	//	mono_export(void, runtime_cleanup, domain_t* domain);
	//	mono_export(int, runtime_exec_main, method_t* method, array_t* args, object_t** exc);
	//	mono_export(void, runtime_exec_managed_code, domain_t* domain, void(*main_func)(void* user_data), void* main_args);
	//	mono_export(object_t*, runtime_invoke, method_t* method, void* obj, void** params, object_t** exc);
	//	mono_export(object_t*, runtime_try_invoke, method_t* method, void* obj, void** params, object_t** exc, error_t* error);
	//	mono_export(object_t*, runtime_invoke_array, method_t* method, void* obj, array_t* params, object_t** exc);
	//	mono_export(object_t*, runtime_delegate_invoke, object_t* delegate, void** params, object_t** exc);
	//	mono_export(array_t*, runtime_get_main_args);
	//	mono_export(std::int32_t, runtime_is_shutting_down);


	//	//signature
	//	mono_export(char*, signature_get_desc, method_signature_t* sig, std::int32_t include_namespace);
	//	mono_export(std::int32_t, signature_explicit_this, method_signature_t* sig);
	//	mono_export(char*, signature_full_name, method_signature_t* sig);
	//	mono_export(uint32_t, signature_get_call_conv, method_signature_t* sig);
	//	mono_export(type_t*, signature_get_params, method_signature_t* sig, void** iter);
	//	mono_export(uint32_t, signature_get_param_count, method_signature_t* sig);
	//	mono_export(type_t*, ignature_get_return_type, method_signature_t* sig);
	//	mono_export(std::uint32_t, signature_hash, method_signature_t* sig);
	//	mono_export(std::int32_t, signature_is_instance, method_signature_t* sig);
	//	mono_export(std::int32_t, signature_param_is_out, method_signature_t* sig, int param_num);
	//	mono_export(int, signature_vararg_start, method_signature_t* sig);
	//	mono_export(void, stack_walk, std::int32_t(*func) (method_t* method, int32_t native_offset, int32_t il_offset, std::int32_t managed, void* data), void* user_data);
	//	mono_export(void, stack_walk_no_il, std::int32_t(*func) (method_t* method, int32_t native_offset, int32_t il_offset, std::int32_t managed, void* data), void* user_data);


	//	//thread
	//	mono_export(thread_t*, thread_get_main);
	//	mono_export(void, thread_set_main, thread_t* thread);
	//	mono_export(internal_thread_t*, thread_internal_current);
	//	mono_export(thread_t*, thread_current);
	//	mono_export(void, thread_new_init, intptr_t tid, void* stack_start, void* func);
	//	mono_export(void, thread_init, void (*start_cb) (std::intptr_t tid, void* stack_start, void* func), void (*attach_cb) (std::intptr_t tid, void* stack_start));
	//	mono_export(void, thread_create, domain_t* domain, void* func, void* arg);
	//	mono_export(thread_t*, thread_attach, domain_t* domain);
	//	mono_export(thread_t*, thread_internal_attach, domain_t* domain);
	//	mono_export(void, thread_detach, thread_t* thread);
	//	mono_export(void, thread_internal_detach, thread_t* thread);
	//	mono_export(std::int32_t, thread_detach_if_exiting);
	//	mono_export(void, thread_cleanup);
	//	mono_export(void, thread_stop, thread_t* thread);
	//	mono_export(void, thread_exit);
	//	mono_export(int32_t, thread_get_managed_id, thread_t* thread);
	//	mono_export(char*, thread_get_name_utf8, thread_t* thread);
	//	mono_export(exception_t*, thread_get_undeniable_exception);
	//	mono_export(std::int32_t, thread_is_foreign, thread_t* thread);
	//	mono_export(void, thread_set_name, internal_thread_t* thread, const char* name8, std::size_t name8_length, const wchar_t* name16, e_set_thread_name_flags flags, error_t* error);
	//	mono_export(std::int32_t, native_thread_create, native_thread_id_t* tid, void* func, void* arg);
	//	mono_export(std::int32_t, native_thread_join, native_thread_id_t tid);
	//	mono_export(std::int32_t, native_thread_id_equals, native_thread_id_t id1, native_thread_id_t id2);
	//	mono_export(native_thread_id_t, native_thread_id_get);
	//	mono_export(void, native_thread_set_name, native_thread_id_t tid, const char* name);

	//	//thread info
	//	mono_export(thread_info_t*, thread_info_current_unchecked);
	//	mono_export(thread_info_t*, thread_info_attach);
	//	mono_export(void, thread_info_detach);
	//	mono_export(e_thread_info_flags, thread_info_get_flags, thread_info_t* info);
	//	mono_export(int, thread_info_get_small_id);
	//	mono_export(void*, thread_info_get_tools_data);
	//	mono_export(void, thread_info_install_interrupt, void (*callback) (void* data), void* data, std::int32_t* interrupted);
	//	mono_export(int, thread_info_register_small_id);
	//	mono_export(void, thread_info_set_flags, e_thread_info_flags flags);
	//	mono_export(std::int32_t, thread_info_set_tools_data, void* data);
	//	mono_export(void, thread_info_uninstall_interrupt, std::int32_t* interrupted);
	//	mono_export(std::int32_t, thread_info_yield);


	//	//type
	//	mono_export(array_type_t*, type_get_array_type, type_t* type);
	//	mono_export(class_t*, type_get_class, type_t* type);
	//	mono_export(reflection_type_t*, type_get_object, domain_t* domain, type_t* type);
	//	mono_export(class_t*, ptr_class_get, type_t* type);
	//	mono_export(type_t*, type_get_ptr_type, type_t* type);
	//	mono_export(type_t*, type_get_underlying_type, type_t* type);
	//	mono_export(int, type_get_type, type_t* type);
	//	mono_export(class_t*, type_get_modifiers, type_t* type, std::int32_t* is_required, void** iter);
	//	mono_export(char*, type_get_name, type_t* type);
	//	mono_export(char*, type_get_name_full, type_t* type, e_type_name_format format);
	//	mono_export(method_signature_t*, type_get_signature, type_t* type);
	//	mono_export(int, type_size, type_t* type, int* alignment);
	//	mono_export(int, type_stack_size, type_t* type, int* alignment);
	//	mono_export(std::int32_t, type_is_byref, type_t* type);
	//	mono_export(std::int32_t, type_is_generic_parameter, type_t* type);
	//	mono_export(std::int32_t, type_is_pointer, type_t* type);
	//	mono_export(std::int32_t, type_is_primitive, type_t* type);
	//	mono_export(std::int32_t, type_is_reference, type_t* type);
	//	mono_export(std::int32_t, type_is_struct, type_t* type);
	//	mono_export(std::int32_t, type_is_valid_enum_basetype, type_t* type);
	//	mono_export(std::int32_t, type_is_void, type_t* type);


	//	//string
	//	mono_export(string_t*, string_new, domain_t* domain, const char* text);
	//	mono_export(string_t*, string_new_checked, domain_t* domain, const char* text, error_t* merror);
	//	mono_export(string_t*, string_new_len, domain_t* domain, const char* text, std::uint32_t length);
	//	mono_export(string_t*, string_new_size, domain_t* domain, int32_t len);
	//	mono_export(string_t*, string_new_utf16, domain_t* domain, const wchar_t* text, std::int32_t len);
	//	mono_export(string_t*, string_new_utf32, domain_t* domain, const std::uint32_t* text, std::int32_t len);
	//	mono_export(string_t*, string_new_wrapper, const char* text);
	//	mono_export(string_t*, string_from_bstr, void* bstr);
	//	mono_export(string_t*, string_from_utf16, wchar_t* data);
	//	mono_export(string_t*, string_from_utf32, std::uint32_t* data);
	//	mono_export(char*, string_to_utf8, string_t* string_obj);
	//	mono_export(char*, string_to_utf8_checked, string_t* string_obj, error_t* error);
	//	mono_export(wchar_t*, string_to_utf16, string_t* string_obj);
	//	mono_export(std::uint32_t*, string_to_utf32, string_t* string_obj);
	//	mono_export(wchar_t*, string_chars, string_t* s);
	//	mono_export(string_t*, string_empty, domain_t* domain);
	//	mono_export(string_t*, string_empty_wrapper);
	//	mono_export(int, string_length, string_t* s);
	//	mono_export(string_t*, string_intern, string_t* str);
	//	mono_export(string_t*, string_is_interned, string_t* str);
	//	mono_export(std::int32_t, string_equal, string_t* s1, string_t* s2);
	//	mono_export(std::uint32_t, string_hash, string_t* s);
	//	mono_export(wchar_t*, unicode_from_external, const char* in, std::size_t* bytes);
	//	mono_export(char*, unicode_to_external, const wchar_t* uni);
	//	mono_export(char*, utf8_from_external, const char* in);
	//	mono_export(std::int32_t, utf8_validate_and_len, const char* source, long* oLength, const char** oEnd);
	//	mono_export(std::int32_t, utf8_validate_and_len_with_bounds, const char* source, long max_bytes, long* oLength, const char** oEnd);


	//	//array
	//	mono_export(std::uintptr_t, array_addr_with_size, array_t* array, int size, uintptr_t idx);
	//	mono_export(class_t*, array_class_get, class_t* eclass, std::uint32_t rank);
	//	mono_export(array_t*, array_clone, array_t* array);
	//	mono_export(std::uint32_t, array_element_size, class_t* ac);
	//	mono_export(std::uintptr_t, array_length, array_t* array);
	//	mono_export(array_t*, array_new, domain_t* domain, class_t* eclass, uintptr_t n);


	//	//value
	//	mono_export(object_t*, value_box, domain_t* domain, class_t* klass, void* val);
	//	mono_export(void, value_copy, void* dest, void* src, class_t* klass);
	//	mono_export(void, value_copy_array, array_t* dest, int dest_idx, void* src, int count);


	//	//object
	//	mono_export(object_t*, object_new, domain_t* domain, class_t* klass);
	//	mono_export(object_t*, object_new_fast, vtable_t* vtable);
	//	mono_export(object_t*, object_new_from_token, domain_t* domain, image_t* image, uint32_t token);
	//	mono_export(object_t*, object_new_specific, vtable_t* vtable);
	//	mono_export(object_t*, object_clone, object_t* obj);
	//	mono_export(class_t*, object_get_class, object_t* obj);
	//	mono_export(domain_t*, object_get_domain, object_t* obj);
	//	mono_export(std::uint32_t, object_get_size, object_t* obj);
	//	mono_export(std::uint32_t, object_get_size_internal, object_t* obj);
	//	mono_export(method_t*, object_get_virtual_method, object_t* obj, method_t* method);
	//	mono_export(vtable_t*, object_get_vtable, object_t* obj);
	//	mono_export(vtable_t*, object_get_vtable_internal, object_t* obj);
	//	mono_export(string_t*, object_to_string, object_t* obj, object_t** exc);
	//	mono_export(void*, object_unbox, object_t* obj);
	//	mono_export(object_t*, object_castclass_mbyref, object_t* obj, class_t* klass);
	//	mono_export(int, object_hash, object_t* obj);


	//	//error
	//	mono_export(void, error_init, error_t* error);
	//	mono_export(void, error_init_flags, error_t* error, unsigned short flags);
	//	mono_export(void, error_cleanup, error_t* error);
	//	mono_export(unsigned short, error_get_error_code, error_t* error);
	//	mono_export(const char*, error_get_message, error_t* error);
	//	mono_export(std::int32_t, error_ok, error_t* error);


	//	//exception
	//	mono_export(void, unhandled_exception, object_t* exc);
	//	mono_export(exception_t*, exception_from_name, image_t* image, const char* name_space, const char* name);
	//	mono_export(exception_t*, exception_from_name_domain, domain_t* domain, image_t* image, const char* name_space, const char* name);
	//	mono_export(exception_t*, exception_from_name_msg, image_t* image, const char* name_space, const char* name, const char* msg);
	//	mono_export(exception_t*, exception_from_name_two_strings, image_t* image, const char* name_space, const char* name, string_t* a1, string_t* a2);
	//	mono_export(exception_t*, exception_from_token, image_t* image, uint32_t token);
	//	mono_export(std::int32_t, exception_walk_trace, exception_t* ex, std::int32_t(*func) (method_t* method, void* ip, size_t native_offset, std::int32_t managed, void* user_data), void* user_data);
	//	mono_export(exception_t*, get_exception_argument, const char* arg, const char* msg);
	//	mono_export(exception_t*, get_exception_argument_null, const char* arg);
	//	mono_export(exception_t*, get_exception_argument_out_of_range, const char* arg);
	//	mono_export(exception_t*, get_exception_arithmetic);
	//	mono_export(exception_t*, get_exception_array_type_mismatch);
	//	mono_export(exception_t*, get_exception_bad_image_format, const char* arg);
	//	mono_export(exception_t*, get_exception_bad_image_format2, const char* msg, string_t* fname);
	//	mono_export(exception_t*, get_exception_cannot_unload_appdomain, const char* msg);
	//	mono_export(exception_t*, get_exception_divide_by_zero);
	//	mono_export(exception_t*, get_exception_execution_engine, const char* msg);
	//	mono_export(exception_t*, get_exception_field_access);
	//	mono_export(exception_t*, get_exception_file_not_found, string_t* fname);
	//	mono_export(exception_t*, get_exception_file_not_found2, const char* msg, string_t* fname);
	//	mono_export(exception_t*, get_exception_index_out_of_range);
	//	mono_export(exception_t*, get_exception_invalid_cast);
	//	mono_export(exception_t*, get_exception_invalid_operation, const char* msg);
	//	mono_export(exception_t*, get_exception_io, const char* msg);
	//	mono_export(exception_t*, get_exception_method_access);
	//	mono_export(exception_t*, get_exception_missing_field, const char* class_name, const char* member_name);
	//	mono_export(exception_t*, get_exception_missing_method, const char* class_name, const char* member_name);
	//	mono_export(exception_t*, get_exception_not_implemented, const char* msg);
	//	mono_export(exception_t*, get_exception_not_supported, const char* msg);
	//	mono_export(exception_t*, get_exception_null_reference);
	//	mono_export(exception_t*, get_exception_out_of_memory);
	//	mono_export(exception_t*, get_exception_overflow);
	//	mono_export(exception_t*, get_exception_reflection_type_load, array_t* types, array_t* exceptions);
	//	mono_export(exception_t*, get_exception_runtime_wrapped, object_t* wrapped_exception);
	//	mono_export(exception_t*, get_exception_security);
	//	mono_export(exception_t*, get_exception_serialization, const char* msg);
	//	mono_export(exception_t*, get_exception_stack_overflow);
	//	mono_export(exception_t*, get_exception_synchronization_lock, const char* msg);
	//	mono_export(exception_t*, get_exception_thread_abort);
	//	mono_export(exception_t*, get_exception_thread_interrupted);
	//	mono_export(exception_t*, get_exception_thread_state, const char* msg);
	//	mono_export(exception_t*, get_exception_type_initialization, const char* type_name, exception_t* inner);
	//	mono_export(exception_t*, get_exception_type_load, string_t* class_name, char* assembly_name);


	//	mono_export(class_t*, get_exception_class);
	//	mono_export(class_t*, get_double_class);
	//	mono_export(class_t*, get_enum_class);
	//	mono_export(class_t*, get_int16_class);
	//	mono_export(class_t*, get_int32_class);
	//	mono_export(class_t*, get_int64_class);
	//	mono_export(class_t*, get_intptr_class);
	//	mono_export(class_t*, get_object_class);
	//	mono_export(class_t*, get_sbyte_class);
	//	mono_export(class_t*, get_single_class);
	//	mono_export(class_t*, get_string_class);
	//	mono_export(class_t*, get_thread_class);
	//	mono_export(class_t*, get_uint16_class);
	//	mono_export(class_t*, get_uint32_class);
	//	mono_export(class_t*, get_uint64_class);
	//	mono_export(class_t*, get_uintptr_class);
	//	mono_export(class_t*, get_void_class);
	//	mono_export(class_t*, get_array_class);
	//	mono_export(class_t*, get_boolean_class);
	//	mono_export(class_t*, get_byte_class);
	//	mono_export(class_t*, get_char_class);

	//	mono_export(type_t*, reflection_type_from_name, const char* name, image_t* image);
	//	mono_export(void, free, void*);
	//} static inline mono{ "" };
}