#pragma once

#include "../types/Timestamp.hpp"
#include "../types/SecurityId.hpp"
#include "../types/SecurityTradingStatus.hpp"
#include "../types/SecurityTradingStatusReason.hpp"

namespace memx::memxequities::memoirdepthfeed::sbe::v1_3 {

#pragma pack(push, 1)

// SecurityTradingStatusMessage
struct SecurityTradingStatusMessage {

    Timestamp timestamp;
    SecurityId security_id;
    SecurityTradingStatus security_trading_status;
    SecurityTradingStatusReason security_trading_status_reason;

    // parse method
    static SecurityTradingStatusMessage* parse(std::byte* buffer) {
        return reinterpret_cast<SecurityTradingStatusMessage*>(buffer);
    }

    // parse method const
    static const SecurityTradingStatusMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const SecurityTradingStatusMessage*>(buffer);
    }
};

#pragma pack(pop)
}
