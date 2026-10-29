#pragma once

#include "../types/BlockLength.hpp"
#include "../types/TemplateId.hpp"
#include "../types/SchemaId.hpp"
#include "../types/Version.hpp"

namespace cme::mdp3::v5 {

#pragma pack(push, 1)

struct SimpleBinaryHeader {

    BlockLength block_length;
    TemplateId template_id;
    SchemaId schema_id;
    Version version;

    // parse method
    static SimpleBinaryHeader* parse(std::byte* buffer) {
        return reinterpret_cast<SimpleBinaryHeader*>(buffer);
    }

    // parse method const
    static const SimpleBinaryHeader* parse(const std::byte* buffer) {
        return reinterpret_cast<const SimpleBinaryHeader*>(buffer);
    }
};

#pragma pack(pop)
}
