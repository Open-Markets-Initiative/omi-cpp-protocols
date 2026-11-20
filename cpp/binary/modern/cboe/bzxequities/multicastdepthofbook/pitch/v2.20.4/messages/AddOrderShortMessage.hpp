// Cboe.BzxEquities.MulticastDepthOfBook.Pitch.v2.20.4: messages/AddOrderShortMessage.hpp
#pragma once

#include "../types/TimeOffset.hpp"
#include "../types/OrderId.hpp"
#include "../types/SideIndicator.hpp"
#include "../types/QuantityShort.hpp"
#include "../types/SymbolShort.hpp"
#include "../types/PriceShort.hpp"
#include "../bitfields/AddFlags.hpp"
#include "../structs/MessageHeader.hpp"

namespace cboe::bzxequities::multicastdepthofbook::pitch::v2_20_4 {

#pragma pack(push, 1)

// Add Order message (short)
struct AddOrderShortMessage {

    TimeOffset time_offset;
    OrderId order_id;
    SideIndicator side_indicator;
    QuantityShort quantity_short;
    SymbolShort symbol_short;
    PriceShort price_short;
    AddFlags add_flags;

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
