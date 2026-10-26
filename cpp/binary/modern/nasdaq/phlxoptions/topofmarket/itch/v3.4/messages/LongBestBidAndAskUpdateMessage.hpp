#pragma once

#include "../types/Nanoseconds.hpp"
#include "../types/OptionId.hpp"
#include "../types/QuoteCondition.hpp"
#include "../types/BidPrice4.hpp"
#include "../types/BidSize4.hpp"
#include "../types/AskPrice4.hpp"
#include "../types/AskSize4.hpp"
#include "../structs/MessageHeader.hpp"

namespace nasdaq::phlxoptions::topofmarket::itch::v3_4 {

#pragma pack(push, 1)

// This message is the same as the Best Bid AND Ask Update Message – Short Form described above except that Prices and Sizes are 4 byte Integers, the prices having 4 implied decimal places.
struct LongBestBidAndAskUpdateMessage {

    Nanoseconds nanoseconds;
    OptionId option_id;
    QuoteCondition quote_condition;
    BidPrice4 bid_price_4;
    BidSize4 bid_size_4;
    AskPrice4 ask_price_4;
    AskSize4 ask_size_4;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'Q';

    // parse method
    static LongBestBidAndAskUpdateMessage* parse(std::byte* buffer) {
        return reinterpret_cast<LongBestBidAndAskUpdateMessage*>(buffer);
    }

    // parse method const
    static const LongBestBidAndAskUpdateMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const LongBestBidAndAskUpdateMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const LongBestBidAndAskUpdateMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const LongBestBidAndAskUpdateMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
