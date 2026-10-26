#pragma once

#include "../types/Nanoseconds.hpp"
#include "../types/OptionId.hpp"
#include "../types/QuoteCondition.hpp"
#include "../types/Price2.hpp"
#include "../types/Size2.hpp"
#include "../structs/MessageHeader.hpp"

namespace nasdaq::phlxoptions::topofmarket::itch::v3_4 {

#pragma pack(push, 1)

// The options system will continuously calculate its best bid and offer position for active options contracts on the options market during the trading day. Whenever the best bid or ask position changes on one side but not the other side, the options system will send its best bid or ask update via this feed for the affected security.
struct ShortBestBidUpdateMessage {

    Nanoseconds nanoseconds;
    OptionId option_id;
    QuoteCondition quote_condition;
    Price2 price_2;
    Size2 size_2;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'b';

    // parse method
    static ShortBestBidUpdateMessage* parse(std::byte* buffer) {
        return reinterpret_cast<ShortBestBidUpdateMessage*>(buffer);
    }

    // parse method const
    static const ShortBestBidUpdateMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const ShortBestBidUpdateMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const ShortBestBidUpdateMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const ShortBestBidUpdateMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
