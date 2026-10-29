#pragma once

#include <cstddef>
#include "../types/BlockLength.hpp"
#include "../types/TemplateId.hpp"
#include "../types/SchemaId.hpp"
#include "../types/Version.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1 {

namespace sbe_binaryentrypoint = ::b3::b3derivatives::binaryentrypoint::sbe::v8_1;

#pragma pack(push, 1)

struct message_header {

    sbe_binaryentrypoint::block_length block_length;
    sbe_binaryentrypoint::template_id template_id;
    sbe_binaryentrypoint::schema_id schema_id;
    sbe_binaryentrypoint::version version;

    // parse method
    static message_header* parse(std::byte* buffer) {
        return reinterpret_cast<message_header*>(buffer);
    }

    // parse method const
    static const message_header* parse(const std::byte* buffer) {
        return reinterpret_cast<const message_header*>(buffer);
    }
};

// layout verification
static_assert(offsetof(message_header, block_length) == 0, "unexpected offset of message_header::block_length");
static_assert(offsetof(message_header, template_id) == 2, "unexpected offset of message_header::template_id");
static_assert(offsetof(message_header, schema_id) == 4, "unexpected offset of message_header::schema_id");
static_assert(offsetof(message_header, version) == 6, "unexpected offset of message_header::version");
static_assert(sizeof(message_header) == 8, "unexpected sizeof message_header");

#pragma pack(pop)
}
