#pragma once

#include "../types/BlockLength.hpp"
#include "../types/TemplateId.hpp"
#include "../types/SchemaId.hpp"
#include "../types/Version.hpp"

namespace memx::memxequities::memoirdepthfeed::sbe::v1_3 {

#pragma pack(push, 1)

struct SbeHeader {

    BlockLength block_length;
    TemplateId template_id;
    SchemaId schema_id;
    Version version;

    // parse method
    static SbeHeader* parse(std::byte* buffer) {
        return reinterpret_cast<SbeHeader*>(buffer);
    }

    // parse method const
    static const SbeHeader* parse(const std::byte* buffer) {
        return reinterpret_cast<const SbeHeader*>(buffer);
    }
};

#pragma pack(pop)
}
