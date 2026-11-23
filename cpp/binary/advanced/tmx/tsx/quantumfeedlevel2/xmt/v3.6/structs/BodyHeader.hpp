// Tmx.Tsx.QuantumFeedLevel2.Xmt.v3.6: structs/BodyHeader.hpp
#pragma once

#include <cstddef>
#include "../types/MsgLength.hpp"
#include "../types/MsgType.hpp"

namespace tmx::tsx::quantumfeedlevel2::xmt::v3_6 {

namespace xmt_quantumfeedlevel2 = ::tmx::tsx::quantumfeedlevel2::xmt::v3_6;

#pragma pack(push, 1)

struct body_header {

    xmt_quantumfeedlevel2::msg_length msg_length;
    xmt_quantumfeedlevel2::msg_type msg_type;

    // parse method
    static body_header* parse(std::byte* buffer) {
        return reinterpret_cast<body_header*>(buffer);
    }

    // parse method const
    static const body_header* parse(const std::byte* buffer) {
        return reinterpret_cast<const body_header*>(buffer);
    }
};

// layout verification
static_assert(offsetof(body_header, msg_length) == 0, "unexpected offset of body_header::msg_length");
static_assert(offsetof(body_header, msg_type) == 2, "unexpected offset of body_header::msg_type");
static_assert(sizeof(body_header) == 3, "unexpected sizeof body_header");

#pragma pack(pop)
}
