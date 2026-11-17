// Siac.Cts.Output.Cta.v2.11.b: structs/TradeMessage.hpp
#pragma once

#include "../types/TradeMessageType.hpp"

namespace siac::cts::output::cta::v2_11_b {

#pragma pack(push, 1)

struct TradeMessage {

    TradeMessageType trade_message_type;

    // parse method
    static TradeMessage* parse(std::byte* buffer) {
        return reinterpret_cast<TradeMessage*>(buffer);
    }

    // parse method const
    static const TradeMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const TradeMessage*>(buffer);
    }
};

#pragma pack(pop)
}
