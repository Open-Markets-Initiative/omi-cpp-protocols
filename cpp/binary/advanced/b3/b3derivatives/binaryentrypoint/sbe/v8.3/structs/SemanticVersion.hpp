#pragma once

#include <cstddef>
#include "../types/MajorNumber.hpp"
#include "../types/MinorNumber.hpp"
#include "../types/PatchNumber.hpp"
#include "../types/BuildNumber.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3 {

namespace sbe_binaryentrypoint = ::b3::b3derivatives::binaryentrypoint::sbe::v8_3;

#pragma pack(push, 1)

struct semantic_version {

    sbe_binaryentrypoint::major_number major_number;
    sbe_binaryentrypoint::minor_number minor_number;
    sbe_binaryentrypoint::patch_number patch_number;
    sbe_binaryentrypoint::build_number build_number;

    // parse method
    static semantic_version* parse(std::byte* buffer) {
        return reinterpret_cast<semantic_version*>(buffer);
    }

    // parse method const
    static const semantic_version* parse(const std::byte* buffer) {
        return reinterpret_cast<const semantic_version*>(buffer);
    }
};

// layout verification
static_assert(offsetof(semantic_version, major_number) == 0, "unexpected offset of semantic_version::major_number");
static_assert(offsetof(semantic_version, minor_number) == 1, "unexpected offset of semantic_version::minor_number");
static_assert(offsetof(semantic_version, patch_number) == 2, "unexpected offset of semantic_version::patch_number");
static_assert(offsetof(semantic_version, build_number) == 3, "unexpected offset of semantic_version::build_number");
static_assert(sizeof(semantic_version) == 4, "unexpected sizeof semantic_version");

#pragma pack(pop)
}
