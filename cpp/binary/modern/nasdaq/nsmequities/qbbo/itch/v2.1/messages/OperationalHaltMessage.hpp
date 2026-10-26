#pragma once

#include "../types/TrackingNumber.hpp"
#include "../types/TimeStamp.hpp"
#include "../types/Stock.hpp"
#include "../types/MarketCode.hpp"
#include "../types/OperationalHaltAction.hpp"
#include "../structs/MessageHeader.hpp"

namespace nasdaq::nsmequities::qbbo::itch::v2_1 {

#pragma pack(push, 1)

// The Exchange uses this message to indicate the current Operational Status of a security to the trading community.
struct OperationalHaltMessage {

    TrackingNumber tracking_number;
    TimeStamp time_stamp;
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
