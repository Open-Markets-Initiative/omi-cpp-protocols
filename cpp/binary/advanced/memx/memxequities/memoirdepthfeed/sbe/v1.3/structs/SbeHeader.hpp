#pragma once

#include <cstddef>
#include "../types/BlockLength.hpp"
#include "../types/TemplateId.hpp"
#include "../types/SchemaId.hpp"
#include "../types/Version.hpp"

namespace memx::memxequities::memoirdepthfeed::sbe::v1_3 {

namespace sbe_memoirdepthfeed = ::memx::memxequities::memoirdepthfeed::sbe::v1_3;

#pragma pack(push, 1)

struct sbe_header {

    sbe_memoirdepthfeed::block_length block_length;
    sbe_memoirdepthfeed::template_id template_id;
    sbe_memoirdepthfeed::schema_id schema_id;
    sbe_memoirdepthfeed::version version;

    // parse method
    static sbe_header* parse(std::byte* buffer) {
        return reinterpret_cast<sbe_header*>(buffer);
    }

    // parse method const
    static const sbe_header* parse(const std::byte* buffer) {
        return reinterpret_cast<const sbe_header*>(buffer);
    }
};

// layout verification
static_assert(offsetof(sbe_header, block_length) == 0, "unexpected offset of sbe_header::block_length");
static_assert(offsetof(sbe_header, template_id) == 2, "unexpected offset of sbe_header::template_id");
static_assert(offsetof(sbe_header, schema_id) == 3, "unexpected offset of sbe_header::schema_id");
static_assert(offsetof(sbe_header, version) == 4, "unexpected offset of sbe_header::version");
static_assert(sizeof(sbe_header) == 6, "unexpected sizeof sbe_header");

#pragma pack(pop)
}
