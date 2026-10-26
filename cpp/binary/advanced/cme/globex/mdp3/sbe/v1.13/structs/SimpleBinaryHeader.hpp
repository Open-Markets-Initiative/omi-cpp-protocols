#pragma once

#include <cstddef>
#include "../types/BlockLength.hpp"
#include "../types/TemplateId.hpp"
#include "../types/SchemaId.hpp"
#include "../types/Version.hpp"

namespace cme::mdp3::v13 {

namespace sbe_mdp3 = ::cme::mdp3::v13;

#pragma pack(push, 1)

struct simple_binary_header {

    sbe_mdp3::block_length block_length;
    sbe_mdp3::template_id template_id;
    sbe_mdp3::schema_id schema_id;
    sbe_mdp3::version version;

    // parse method
    static simple_binary_header* parse(std::byte* buffer) {
        return reinterpret_cast<simple_binary_header*>(buffer);
    }

    // parse method const
    static const simple_binary_header* parse(const std::byte* buffer) {
        return reinterpret_cast<const simple_binary_header*>(buffer);
    }
};

// layout verification
static_assert(offsetof(simple_binary_header, block_length) == 0, "unexpected offset of simple_binary_header::block_length");
static_assert(offsetof(simple_binary_header, template_id) == 2, "unexpected offset of simple_binary_header::template_id");
static_assert(offsetof(simple_binary_header, schema_id) == 4, "unexpected offset of simple_binary_header::schema_id");
static_assert(offsetof(simple_binary_header, version) == 6, "unexpected offset of simple_binary_header::version");
static_assert(sizeof(simple_binary_header) == 8, "unexpected sizeof simple_binary_header");

#pragma pack(pop)
}
