#pragma once

#include "../types/Timestamp.hpp"
#include "../types/TradingSession.hpp"

namespace memx::memxequities::memoirdepthfeed::sbe::v1_3 {

#pragma pack(push, 1)

// TradingSessionStatusMessage
struct TradingSessionStatusMessage {

    Timestamp timestamp;
    TradingSession trading_session;

    // parse method
    static TradingSessionStatusMessage* parse(std::byte* buffer) {
        return reinterpret_cast<TradingSessionStatusMessage*>(buffer);
    }

    // parse method const
    static const TradingSessionStatusMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const TradingSessionStatusMessage*>(buffer);
    }
};

#pragma pack(pop)
}
