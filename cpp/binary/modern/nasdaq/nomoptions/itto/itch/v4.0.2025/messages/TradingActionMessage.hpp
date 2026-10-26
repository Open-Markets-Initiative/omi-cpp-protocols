#pragma once

#include "../types/TrackingNumber.hpp"
#include "../types/Timestamp.hpp"
#include "../types/OptionId.hpp"
#include "../types/CurrentTradingState.hpp"
#include "../structs/MessageHeader.hpp"

namespace nasdaq::nomoptions::itto::itch::v4_0_2025 {

#pragma pack(push, 1)

// After the start of system hours, NASDAQ will use the Trading Action message to relay changes in trading status for an individual option. Messages will be sent when an option is halted, is released for quotation, released for trading, or temporarily suspended for trading on the buy or sell side.
struct TradingActionMessage {

    TrackingNumber tracking_number;
    Timestamp timestamp;
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
