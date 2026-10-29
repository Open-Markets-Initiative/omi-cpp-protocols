#pragma once

#include "../types/MajorNumber.hpp"
#include "../types/MinorNumber.hpp"
#include "../types/PatchNumber.hpp"
#include "../types/BuildNumber.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3 {

#pragma pack(push, 1)

struct SemanticVersion {

    MajorNumber major_number;
    MinorNumber minor_number;
    PatchNumber patch_number;
    BuildNumber build_number;

    // parse method
    static SemanticVersion* parse(std::byte* buffer) {
        return reinterpret_cast<SemanticVersion*>(buffer);
    }

    // parse method const
    static const SemanticVersion* parse(const std::byte* buffer) {
        return reinterpret_cast<const SemanticVersion*>(buffer);
    }
};

#pragma pack(pop)
}
