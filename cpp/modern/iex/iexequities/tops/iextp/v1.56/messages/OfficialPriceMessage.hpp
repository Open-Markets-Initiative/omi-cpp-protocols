#pragma once

#include "../types/PriceType.hpp"
#include "../types/Timestamp.hpp"
#include "../types/Symbol.hpp"
#include "../types/OfficialPrice.hpp"
#include "../structs/MessageHeader.hpp"

namespace iex::iexequities::tops::iextp::v1_56 {

#pragma pack(push, 1)

// Official Price Messages are sent for each IEX-listed security to indicate the IEX Official Opening Price and IEX Official Closing Price.
struct OfficialPriceMessage {

    PriceType price_type;
    Timestamp timestamp;
    Symbol symbol;
    OfficialPrice official_price;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'X';

    // parse method
    static OfficialPriceMessage* parse(std::byte* buffer) {
        return reinterpret_cast<OfficialPriceMessage*>(buffer);
    }

    // parse method const
    static const OfficialPriceMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const OfficialPriceMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const OfficialPriceMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const OfficialPriceMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
