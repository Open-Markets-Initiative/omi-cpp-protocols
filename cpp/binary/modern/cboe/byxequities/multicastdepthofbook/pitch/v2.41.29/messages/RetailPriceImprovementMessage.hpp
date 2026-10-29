#pragma once

#include "../types/TimeOffset.hpp"
#include "../types/SymbolLong.hpp"
#include "../types/RetailPriceImprovement.hpp"
#include "../structs/MessageHeader.hpp"

namespace cboe::byxequities::multicastdepthofbook::pitch::v2_41_29 {

#pragma pack(push, 1)

// This message is a Retail Liquidity Indicator (RLI) that includes symbol and side, but not price and size
struct RetailPriceImprovementMessage {

    TimeOffset time_offset;
    SymbolLong symbol_long;
    RetailPriceImprovement retail_price_improvement;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint8_t message_type = 0x98;

    // parse method
    static RetailPriceImprovementMessage* parse(std::byte* buffer) {
        return reinterpret_cast<RetailPriceImprovementMessage*>(buffer);
    }

    // parse method const
    static const RetailPriceImprovementMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const RetailPriceImprovementMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const RetailPriceImprovementMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const RetailPriceImprovementMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
