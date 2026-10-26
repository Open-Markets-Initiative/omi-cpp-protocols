#pragma once

#include "../types/TrackingNumber.hpp"
#include "../types/Timestamp.hpp"
#include "../types/BidReferenceNumber.hpp"
#include "../types/AskReferenceNumber.hpp"
#include "../types/OptionId.hpp"
#include "../types/BidPriceShort.hpp"
#include "../types/BidSizeShort.hpp"
#include "../types/AskPriceShort.hpp"
#include "../types/AskSizeShort.hpp"
#include "../structs/MessageHeader.hpp"

namespace nasdaq::nomoptions::itto::itch::v4_0_2025 {

#pragma pack(push, 1)

// For bandwidth efficiency reasons, this message can be published in either short or long format.
struct AddQuoteMessageShortFormMessage {

    TrackingNumber tracking_number;
    Timestamp timestamp;
    BidReferenceNumber bid_reference_number;
    AskReferenceNumber ask_reference_number;
    OptionId option_id;
    BidPriceShort bid_price_short;
    BidSizeShort bid_size_short;
    AskPriceShort ask_price_short;
    AskSizeShort ask_size_short;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'j';

    // parse method
    static AddQuoteMessageShortFormMessage* parse(std::byte* buffer) {
        return reinterpret_cast<AddQuoteMessageShortFormMessage*>(buffer);
    }

    // parse method const
    static const AddQuoteMessageShortFormMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const AddQuoteMessageShortFormMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const AddQuoteMessageShortFormMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const AddQuoteMessageShortFormMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
