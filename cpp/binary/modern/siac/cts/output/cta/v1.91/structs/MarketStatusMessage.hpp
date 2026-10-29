#pragma once

#include "../types/MarketStatusMessageType.hpp"

namespace siac::cts::output::cta::v1_91 {

#pragma pack(push, 1)

struct MarketStatusMessage {

    MarketStatusMessageType market_status_message_type;

    // parse method
    static MarketStatusMessage* parse(std::byte* buffer) {
        return reinterpret_cast<MarketStatusMessage*>(buffer);
    }

    // parse method const
    static const MarketStatusMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const MarketStatusMessage*>(buffer);
    }
};

#pragma pack(pop)
}
