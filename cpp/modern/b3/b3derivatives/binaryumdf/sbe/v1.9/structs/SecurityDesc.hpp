#pragma once

#include "../types/SecurityDescLength.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v1_9 {

#pragma pack(push, 1)

struct SecurityDesc {

    SecurityDescLength security_desc_length;

    // parse method
    static SecurityDesc* parse(std::byte* buffer) {
        return reinterpret_cast<SecurityDesc*>(buffer);
    }

    // parse method const
    static const SecurityDesc* parse(const std::byte* buffer) {
        return reinterpret_cast<const SecurityDesc*>(buffer);
    }
};

#pragma pack(pop)
}
