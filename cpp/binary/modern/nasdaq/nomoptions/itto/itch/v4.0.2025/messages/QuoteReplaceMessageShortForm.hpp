#pragma once

#include "../types/TrackingNumber.hpp"
#include "../types/Timestamp.hpp"
#include "../types/OriginalBidReferenceNumber.hpp"
#include "../types/BidReferenceNumber.hpp"
#include "../types/OriginalAskReferenceNumber.hpp"
#include "../types/AskReferenceNumber.hpp"
#include "../types/BidPriceShort.hpp"
#include "../types/BidSizeShort.hpp"
#include "../types/AskPriceShort.hpp"
#include "../types/AskSizeShort.hpp"
#include "../structs/MessageHeader.hpp"

namespace nasdaq::nomoptions::itto::itch::v4_0_2025 {

#pragma pack(push, 1)

// This message is sent whenever a quote on the book is replaced. The replaced quote has new sequence numbers on both sides. These new sequence numbers replace the prior sequence numbers on the quote.
struct QuoteReplaceMessageShortForm {

    TrackingNumber tracking_number;
    Timestamp timestamp;
    OriginalBidReferenceNumber original_bid_reference_number;
    BidReferenceNumber bid_reference_number;
    OriginalAskReferenceNumber original_ask_reference_number;
    AskReferenceNumber ask_reference_number;
    BidPriceShort bid_price_short;
    BidSizeShort bid_size_short;
    AskPriceShort ask_price_short;
    AskSizeShort ask_size_short;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'k';

    // parse method
    static QuoteReplaceMessageShortForm* parse(std::byte* buffer) {
        return reinterpret_cast<QuoteReplaceMessageShortForm*>(buffer);
    }

    // parse method const
    static const QuoteReplaceMessageShortForm* parse(const std::byte* buffer) {
        return reinterpret_cast<const QuoteReplaceMessageShortForm*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const QuoteReplaceMessageShortForm* parse(const MessageHeader* header) {
        return reinterpret_cast<const QuoteReplaceMessageShortForm*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
