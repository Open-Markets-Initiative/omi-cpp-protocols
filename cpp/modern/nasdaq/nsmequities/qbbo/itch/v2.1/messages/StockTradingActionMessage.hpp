#pragma once

#include "../types/TrackingNumber.hpp"
#include "../types/TimeStamp.hpp"
#include "../types/Stock.hpp"
#include "../types/SecurityClass.hpp"
#include "../types/CurrentTradingState.hpp"
#include "../types/Reason.hpp"
#include "../structs/MessageHeader.hpp"

namespace nasdaq::nsmequities::qbbo::itch::v2_1 {

#pragma pack(push, 1)

// Nasdaq uses this administrative message to indicate the current trading status of a security to the trading community.
struct StockTradingActionMessage {

    TrackingNumber tracking_number;
    TimeStamp time_stamp;
    Stock stock;
    SecurityClass security_class;
    CurrentTradingState current_trading_state;
    Reason reason;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'H';

    // parse method
    static StockTradingActionMessage* parse(std::byte* buffer) {
        return reinterpret_cast<StockTradingActionMessage*>(buffer);
    }

    // parse method const
    static const StockTradingActionMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const StockTradingActionMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const StockTradingActionMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const StockTradingActionMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
