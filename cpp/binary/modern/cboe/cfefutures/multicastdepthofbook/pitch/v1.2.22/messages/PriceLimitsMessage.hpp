#pragma once

#include "../types/TimeOffset.hpp"
#include "../types/Symbol.hpp"
#include "../types/UpperPriceLimit.hpp"
#include "../types/LowerPriceLimit.hpp"
#include "../structs/MessageHeader.hpp"

namespace cboe::cfefutures::multicastdepthofbook::pitch::v1_2_22 {

#pragma pack(push, 1)

// The Price Limits message is sent out at the start of a session for products subject to price limits per the contract specifications.
struct PriceLimitsMessage {

    TimeOffset time_offset;
    Symbol symbol;
    UpperPriceLimit upper_price_limit;
    LowerPriceLimit lower_price_limit;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint8_t message_type = 0xBE;

    // parse method
    static PriceLimitsMessage* parse(std::byte* buffer) {
        return reinterpret_cast<PriceLimitsMessage*>(buffer);
    }

    // parse method const
    static const PriceLimitsMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const PriceLimitsMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const PriceLimitsMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const PriceLimitsMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
