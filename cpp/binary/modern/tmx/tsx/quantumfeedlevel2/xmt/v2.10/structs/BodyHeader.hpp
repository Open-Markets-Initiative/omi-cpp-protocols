#pragma once

#include "../types/MsgLength.hpp"
#include "../types/MsgType.hpp"

namespace tmx::tsx::quantumfeedlevel2::xmt::v2_10 {

#pragma pack(push, 1)

struct BodyHeader {

    MsgLength msg_length;
    MsgType msg_type;

    // parse method
    static BodyHeader* parse(std::byte* buffer) {
        return reinterpret_cast<BodyHeader*>(buffer);
    }

    // parse method const
    static const BodyHeader* parse(const std::byte* buffer) {
        return reinterpret_cast<const BodyHeader*>(buffer);
    }
};

#pragma pack(pop)
}
