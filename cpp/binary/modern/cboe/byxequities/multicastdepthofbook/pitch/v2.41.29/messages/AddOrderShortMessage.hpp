#pragma once

#include "../types/TimeOffset.hpp"
#include "../types/OrderId.hpp"
#include "../types/SideIndicator.hpp"
#include "../types/QuantityShort.hpp"
#include "../types/SymbolShort.hpp"
#include "../types/PriceShort.hpp"
#include "../bitfields/AddOrderFlags.hpp"
#include "../structs/MessageHeader.hpp"

namespace cboe::byxequities::multicastdepthofbook::pitch::v2_41_29 {

#pragma pack(push, 1)

// An Add Order message represents a newly accepted visible order on the Cboe book.
struct AddOrderShortMessage {

    TimeOffset time_offset;
    OrderId order_id;
    SideIndicator side_indicator;
    QuantityShort quantity_short;
    SymbolShort symbol_short;
    PriceShort price_short;
    AddOrderFlags add_order_flags;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint8_t message_type = 0x22;

    // parse method
    static AddOrderShortMessage* parse(std::byte* buffer) {
        return reinterpret_cast<AddOrderShortMessage*>(buffer);
    }

    // parse method const
    static const AddOrderShortMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const AddOrderShortMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const AddOrderShortMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const AddOrderShortMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
