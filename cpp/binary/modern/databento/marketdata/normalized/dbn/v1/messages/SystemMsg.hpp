#pragma once

#include "../types/Msg.hpp"

namespace databento::marketdata::normalized::dbn::v1 {

#pragma pack(push, 1)

// A non-error message from the Databento Live Subscription Gateway (LSG); also used for heartbeating
struct SystemMsg {

    Msg msg;

    // parse method
    static SystemMsg* parse(std::byte* buffer) {
        return reinterpret_cast<SystemMsg*>(buffer);
    }

    // parse method const
    static const SystemMsg* parse(const std::byte* buffer) {
        return reinterpret_cast<const SystemMsg*>(buffer);
    }
};

#pragma pack(pop)
}
