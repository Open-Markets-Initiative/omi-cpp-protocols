#pragma once

#include "../types/TimeOffset.hpp"
#include "../types/OrderId.hpp"
#include "../types/SideIndicator.hpp"
#include "../types/LongQuantity.hpp"
#include "../types/ExpandedSymbol.hpp"
#include "../types/LongPrice.hpp"
#include "../bitfields/AddFlags.hpp"
#include "../types/ParticipantId.hpp"
#include "../types/CustomerIndicator.hpp"
#include "../structs/MessageHeader.hpp"

namespace cboe::c1options::multicastdepthofbook::pitch::v2_39_4 {

#pragma pack(push, 1)

// An Add Order message represents a newly accepted visible order on the Cboe book. Expanded version accommodates larger symbol sizes possible through the ISRA plan.
struct AddOrderExpandedMessage {

    TimeOffset time_offset;
    OrderId order_id;
    SideIndicator side_indicator;
    LongQuantity long_quantity;
    ExpandedSymbol expanded_symbol;
    LongPrice long_price;
    AddFlags add_flags;
    ParticipantId participant_id;
    CustomerIndicator customer_indicator;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint8_t message_type = 0x2F;

    // parse method
    static AddOrderExpandedMessage* parse(std::byte* buffer) {
        return reinterpret_cast<AddOrderExpandedMessage*>(buffer);
    }

    // parse method const
    static const AddOrderExpandedMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const AddOrderExpandedMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const AddOrderExpandedMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const AddOrderExpandedMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
