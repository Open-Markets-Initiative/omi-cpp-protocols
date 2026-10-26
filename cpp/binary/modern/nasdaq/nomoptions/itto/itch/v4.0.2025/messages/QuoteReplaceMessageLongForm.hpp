#pragma once

#include "../types/TrackingNumber.hpp"
#include "../types/Timestamp.hpp"
#include "../types/OriginalBidReferenceNumber.hpp"
#include "../types/BidReferenceNumber.hpp"
#include "../types/OriginalAskReferenceNumber.hpp"
#include "../types/AskReferenceNumber.hpp"
#include "../types/BidPriceLong.hpp"
#include "../types/BidSizeLong.hpp"
#include "../types/AskPriceLong.hpp"
#include "../types/AskSizeLong.hpp"
#include "../structs/MessageHeader.hpp"

namespace nasdaq::nomoptions::itto::itch::v4_0_2025 {

#pragma pack(push, 1)

// This message is sent whenever a quote on the book is replaced. The replaced quote has new sequence numbers on both sides. These new sequence numbers replace the prior sequence numbers on the quote.
struct QuoteReplaceMessageLongForm {

    TrackingNumber tracking_number;
    Timestamp timestamp;
    OriginalBidReferenceNumber original_bid_reference_number;
    BidReferenceNumber bid_reference_number;
    OriginalAskReferenceNumber original_ask_reference_number;
    AskReferenceNumber ask_reference_number;
    BidPriceLong bid_price_long;
    BidSizeLong bid_size_long;
    AskPriceLong ask_price_long;
    AskSizeLong ask_size_long;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'K';

    // parse method
    static QuoteReplaceMessageLongForm* parse(std::byte* buffer) {
        return reinterpret_cast<QuoteReplaceMessageLongForm*>(buffer);
    }

    // parse method const
    static const QuoteReplaceMessageLongForm* parse(const std::byte* buffer) {
        return reinterpret_cast<const QuoteReplaceMessageLongForm*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const QuoteReplaceMessageLongForm* parse(const MessageHeader* header) {
        return reinterpret_cast<const QuoteReplaceMessageLongForm*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
