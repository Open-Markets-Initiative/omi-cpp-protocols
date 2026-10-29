#pragma once

#include "../types/StockLocate.hpp"
#include "../types/TrackingNumber.hpp"
#include "../types/Timestamp.hpp"
#include "../types/Stock.hpp"
#include "../types/MarketCode.hpp"
#include "../types/OperationalHaltAction.hpp"
#include "../structs/MessageHeader.hpp"

namespace nasdaq::ntxequities::totalview::itch::v5_0 {

#pragma pack(push, 1)

// The Exchange uses this message to indicate the current Operational Status of a security to the trading community.
struct OperationalHaltMessage {

    StockLocate stock_locate;
    TrackingNumber tracking_number;
    Timestamp timestamp;
    Stock stock;
    MarketCode market_code;
    OperationalHaltAction operational_halt_action;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'h';

    // parse method
    static OperationalHaltMessage* parse(std::byte* buffer) {
        return reinterpret_cast<OperationalHaltMessage*>(buffer);
    }

    // parse method const
    static const OperationalHaltMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const OperationalHaltMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const OperationalHaltMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const OperationalHaltMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
