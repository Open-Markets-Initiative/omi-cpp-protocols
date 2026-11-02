#pragma once

#include "../types/Magic.hpp"
#include "../types/Version.hpp"
#include "../types/MetadataLength.hpp"
#include "../types/Dataset.hpp"
#include "../types/Schema.hpp"
#include "../types/Start.hpp"
#include "../types/End.hpp"
#include "../types/Limit.hpp"
#include "../types/MetadataReserved8.hpp"
#include "../types/StypeIn.hpp"
#include "../types/StypeOut.hpp"
#include "../types/TsOut.hpp"
#include "../types/MetadataReserved.hpp"
#include "../types/SchemaDefinitionLength.hpp"

namespace databento::marketdata::normalized::dbn::v1 {

#pragma pack(push, 1)

struct Metadata {

    Magic magic;
    Version version;
    MetadataLength metadata_length;
    Dataset dataset;
    Schema schema;
    Start start;
    End end;
    Limit limit;
    MetadataReserved8 metadata_reserved_8;
    StypeIn stype_in;
    StypeOut stype_out;
    TsOut ts_out;
    MetadataReserved metadata_reserved;
    SchemaDefinitionLength schema_definition_length;

    // parse method
    static Metadata* parse(std::byte* buffer) {
        return reinterpret_cast<Metadata*>(buffer);
    }

    // parse method const
    static const Metadata* parse(const std::byte* buffer) {
        return reinterpret_cast<const Metadata*>(buffer);
    }
};

#pragma pack(pop)
}
