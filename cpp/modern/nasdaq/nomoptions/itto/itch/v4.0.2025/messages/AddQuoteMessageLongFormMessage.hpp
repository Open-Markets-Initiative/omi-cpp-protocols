#pragma once

#include "../types/TrackingNumber.hpp"
#include "../types/Timestamp.hpp"
#include "../types/BidReferenceNumber.hpp"
#include "../types/AskReferenceNumber.hpp"
#include "../types/OptionId.hpp"
#include "../types/Bid.hpp"
#include "../types/BidSizeLong.hpp"
#include "../types/Ask.hpp"
#include "../types/AskSizeLong.hpp"
#include "../structs/MessageHeader.hpp"

namespace nasdaq::nomoptions::itto::itch::v4_0_2025 {

#pragma pack(push, 1)

// For bandwidth efficiency reasons, this message can be published in either short or long format.
struct AddQuoteMessageLongFormMessage {

    TrackingNumber tracking_number;
    Timestamp timestamp;
    BidReferenceNumber bid_reference_number;
    AskReferenceNumber ask_reference_number;
    OptionId option_id;
    Bid bid;
    BidSizeLong bid_size_long;
    Ask ask;
    AskSizeLong ask_size_long;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'J';

    // parse method
    static AddQuoteMessageLongFormMessage* parse(std::byte* buffer) {
        return reinterpret_cast<AddQuoteMessageLongFormMessage*>(buffer);
    }

    // parse method const
    static const AddQuoteMessageLongFormMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const AddQuoteMessageLongFormMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const AddQuoteMessageLongFormMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const AddQuoteMessageLongFormMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
