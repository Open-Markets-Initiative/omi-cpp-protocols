#pragma once

#include "../types/Text.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

#pragma pack(push, 1)

// Debug packets are intended to provide human readable text that may aid in debugging problems
struct DebugPacket {

    Text text;

    // parse method
    static DebugPacket* parse(std::byte* buffer) {
        return reinterpret_cast<DebugPacket*>(buffer);
    }

    // parse method const
    static const DebugPacket* parse(const std::byte* buffer) {
        return reinterpret_cast<const DebugPacket*>(buffer);
    }
};

#pragma pack(pop)
}
