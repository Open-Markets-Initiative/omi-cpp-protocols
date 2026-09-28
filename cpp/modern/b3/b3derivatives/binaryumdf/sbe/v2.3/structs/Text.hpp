#pragma once

#include "../types/TextLength.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v2_3 {

#pragma pack(push, 1)

struct Text {

    TextLength text_length;

    // parse method
    static Text* parse(std::byte* buffer) {
        return reinterpret_cast<Text*>(buffer);
    }

    // parse method const
    static const Text* parse(const std::byte* buffer) {
        return reinterpret_cast<const Text*>(buffer);
    }
};

#pragma pack(pop)
}
