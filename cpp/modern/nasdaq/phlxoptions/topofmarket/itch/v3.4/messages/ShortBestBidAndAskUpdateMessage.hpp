#pragma once

#include "../types/Nanoseconds.hpp"
#include "../types/OptionId.hpp"
#include "../types/QuoteCondition.hpp"
#include "../types/BidPrice2.hpp"
#include "../types/BidSize2.hpp"
#include "../types/AskPrice2.hpp"
#include "../types/AskSize2.hpp"
#include "../structs/MessageHeader.hpp"

namespace nasdaq::phlxoptions::topofmarket::itch::v3_4 {

#pragma pack(push, 1)

// Whenever the best bid and ask position changes on both sides, the options system will send its best bid and ask update via the data feed for the affected security.
struct ShortBestBidAndAskUpdateMessage {

    Nanoseconds nanoseconds;
    OptionId option_id;
    QuoteCondition quote_condition;
    BidPrice2 bid_price_2;
    BidSize2 bid_size_2;
    AskPrice2 ask_price_2;
    AskSize2 ask_size_2;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'q';

    // parse method
    static ShortBestBidAndAskUpdateMessage* parse(std::byte* buffer) {
        return reinterpret_cast<ShortBestBidAndAskUpdateMessage*>(buffer);
    }

    // parse method const
    static const ShortBestBidAndAskUpdateMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const ShortBestBidAndAskUpdateMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const ShortBestBidAndAskUpdateMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const ShortBestBidAndAskUpdateMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
