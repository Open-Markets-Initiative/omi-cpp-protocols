#pragma once

#include "../types/Nanoseconds.hpp"
#include "../types/OptionId.hpp"
#include "../types/QuoteCondition.hpp"
#include "../types/Price4.hpp"
#include "../types/Size4.hpp"
#include "../structs/MessageHeader.hpp"

namespace nasdaq::phlxoptions::topofmarket::itch::v3_4 {

#pragma pack(push, 1)

// This message is the same as the Best Bid OR Ask Update Message – Short Form described above except that Prices and Sizes are 4 byte Integers, the price having 4 implied decimal places.
struct LongBestAskUpdateMessage {

    Nanoseconds nanoseconds;
    OptionId option_id;
    QuoteCondition quote_condition;
    Price4 price_4;
    Size4 size_4;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'A';

    // parse method
    static LongBestAskUpdateMessage* parse(std::byte* buffer) {
        return reinterpret_cast<LongBestAskUpdateMessage*>(buffer);
    }

    // parse method const
    static const LongBestAskUpdateMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const LongBestAskUpdateMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const LongBestAskUpdateMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const LongBestAskUpdateMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
