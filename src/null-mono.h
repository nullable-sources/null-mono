#pragma once
#include <mono/domain/domain.h>
#include <mono/thread/thread.h>
#include <mono/assembly/assembly.h>

#include <mono/array/array.h>
#include <mono/string/string.h>
#include <mono/object/object.h>
#include <mono/type/type.h>

#include <mono/class/class.h>
#include <mono/field/field.h>
#include <mono/method/method.h>
#include <mono/property/property.h>

#include <mono/exports.h>

#include <std/collections/list.h>

namespace mono {
    struct parser_t {
        std::string assembly{ }, name_space{ }, klass{ }, member{ };

        parser_t(std::string str);
    };
}