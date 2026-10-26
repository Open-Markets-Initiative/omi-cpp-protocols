#pragma once

#include "../types/TimeOffset.hpp"
#include "../types/Symbol.hpp"
#include "../types/TradeDate.hpp"
#include "../types/OpenInterest.hpp"
#include "../structs/MessageHeader.hpp"

namespace cboe::cfefutures::multicastdepthofbook::pitch::v1_2_22 {

#pragma pack(push, 1)

// The Open Interest message is sent to communicate a symbol's open interest, usually for the prior trading date.
struct OpenInterestMessage {

    TimeOffset time_offset;
    Symbol symbol;
    TradeDate trade_date;
    OpenInterest open_interest;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint8_t message_type = 0xD3;

    // parse method
    static OpenInterestMessage* parse(std::byte* buffer) {
        return reinterpret_cast<OpenInterestMessage*>(buffer);
    }

    // parse method const
    static const OpenInterestMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const OpenInterestMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const OpenInterestMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const OpenInterestMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
