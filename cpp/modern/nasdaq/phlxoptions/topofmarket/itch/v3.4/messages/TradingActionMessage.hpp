#pragma once

#include "../types/Nanoseconds.hpp"
#include "../types/OptionId.hpp"
#include "../types/CurrentTradingState.hpp"
#include "../structs/MessageHeader.hpp"

namespace nasdaq::phlxoptions::topofmarket::itch::v3_4 {

#pragma pack(push, 1)

// The options system uses this administrative message to indicate the current trading status of an index or equity option within the options market.
struct TradingActionMessage {

    Nanoseconds nanoseconds;
    OptionId option_id;
    CurrentTradingState current_trading_state;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'H';

    // parse method
    static TradingActionMessage* parse(std::byte* buffer) {
        return reinterpret_cast<TradingActionMessage*>(buffer);
    }

    // parse method const
    static const TradingActionMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const TradingActionMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const TradingActionMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const TradingActionMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
