#pragma once

#include "../types/TrackingNumber.hpp"
#include "../types/Timestamp.hpp"
#include "../types/BidReferenceNumber.hpp"
#include "../types/AskReferenceNumber.hpp"
#include "../structs/MessageHeader.hpp"

namespace nasdaq::nomoptions::itto::itch::v4_0_2025 {

#pragma pack(push, 1)

// The message is sent when a single quote is being cancelled. All remaining contracts are no longer accessible so the quote should be removed from the book.
struct QuoteDeleteMessage {

    TrackingNumber tracking_number;
    Timestamp timestamp;
    BidReferenceNumber bid_reference_number;
    AskReferenceNumber ask_reference_number;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'Y';

    // parse method
    static QuoteDeleteMessage* parse(std::byte* buffer) {
        return reinterpret_cast<QuoteDeleteMessage*>(buffer);
    }

    // parse method const
    static const QuoteDeleteMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const QuoteDeleteMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const QuoteDeleteMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const QuoteDeleteMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
