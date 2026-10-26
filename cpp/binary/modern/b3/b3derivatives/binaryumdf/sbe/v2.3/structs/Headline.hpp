#pragma once

#include "../types/HeadlineLength.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v2_3 {

#pragma pack(push, 1)

struct Headline {

    HeadlineLength headline_length;

    // parse method
    static Headline* parse(std::byte* buffer) {
        return reinterpret_cast<Headline*>(buffer);
    }

    // parse method const
    static const Headline* parse(const std::byte* buffer) {
        return reinterpret_cast<const Headline*>(buffer);
    }
};

#pragma pack(pop)
}
