#pragma once

#include "../types/TimeOffset.hpp"
#include "../types/Symbol.hpp"
#include "../types/TradeDate.hpp"
#include "../types/SettlementPrice.hpp"
#include "../types/Issue.hpp"
#include "../structs/MessageHeader.hpp"

namespace cboe::cfefutures::multicastdepthofbook::pitch::v1_2_22 {

#pragma pack(push, 1)

// Settlement messages are used to provide information concerning indicative, approved, or corrected daily and final settlement prices for CFE products.
struct SettlementMessage {

    TimeOffset time_offset;
    Symbol symbol;
    TradeDate trade_date;
    SettlementPrice settlement_price;
    Issue issue;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint8_t message_type = 0xB9;

    // parse method
    static SettlementMessage* parse(std::byte* buffer) {
        return reinterpret_cast<SettlementMessage*>(buffer);
    }

    // parse method const
    static const SettlementMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const SettlementMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const SettlementMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const SettlementMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
