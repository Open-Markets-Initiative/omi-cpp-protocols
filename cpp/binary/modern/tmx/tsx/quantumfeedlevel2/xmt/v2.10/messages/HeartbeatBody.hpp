#pragma once

#include "../structs/BodyHeader.hpp"
#include "../types/AdminId.hpp"
#include "../types/HbInterval.hpp"

namespace tmx::tsx::quantumfeedlevel2::xmt::v2_10 {

#pragma pack(push, 1)

// 
struct HeartbeatBody {

    BodyHeader body_header;
    AdminId admin_id;
    HbInterval hb_interval;

    // parse method
    static HeartbeatBody* parse(std::byte* buffer) {
        return reinterpret_cast<HeartbeatBody*>(buffer);
    }

    // parse method const
    static const HeartbeatBody* parse(const std::byte* buffer) {
        return reinterpret_cast<const HeartbeatBody*>(buffer);
    }
};

#pragma pack(pop)
}
