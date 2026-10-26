#pragma once

#include "../types/ShortSalePriceTestStatus.hpp"
#include "../types/Timestamp.hpp"
#include "../types/Symbol.hpp"
#include "../types/Detail.hpp"
#include "../structs/MessageHeader.hpp"

namespace iex::iexequities::tops::iextp::v1_64 {

#pragma pack(push, 1)

// The Short Sale Price Test Message is used to indicate when a short sale price test restriction is in effect for a security.
struct ShortSalePriceTestStatusMessage {

    ShortSalePriceTestStatus short_sale_price_test_status;
    Timestamp timestamp;
    Symbol symbol;
    Detail detail;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'P';

    // parse method
    static ShortSalePriceTestStatusMessage* parse(std::byte* buffer) {
        return reinterpret_cast<ShortSalePriceTestStatusMessage*>(buffer);
    }

    // parse method const
    static const ShortSalePriceTestStatusMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const ShortSalePriceTestStatusMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const ShortSalePriceTestStatusMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const ShortSalePriceTestStatusMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
