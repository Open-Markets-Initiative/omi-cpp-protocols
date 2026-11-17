// Databento.MarketData.Normalized.Dbn.v2: messages/SystemMsg.hpp
#pragma once

#include "../types/Msg.hpp"
#include "../types/SystemCode.hpp"

namespace databento::marketdata::normalized::dbn::v2 {

#pragma pack(push, 1)

// A non-error message from the Databento Live Subscription Gateway (LSG); also used for heartbeating
struct SystemMsg {

    Msg msg;
    SystemCode system_code;

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
