#pragma once

#include "../types/TimeOffset.hpp"
#include "../types/OrderId.hpp"
#include "../types/SideIndicator.hpp"
#include "../types/QuantityLong.hpp"
#include "../types/ExpandedSymbol.hpp"
#include "../types/PriceLong.hpp"
#include "../bitfields/AddFlags.hpp"
#include "../types/ParticipantId.hpp"
#include "../types/CustomerIndicator.hpp"
#include "../types/ClientId.hpp"
#include "../types/Reserved5.hpp"
#include "../structs/MessageHeader.hpp"

namespace cboe::edgxoptions::multicastdepthofbook::pitch::v2_41_80 {

#pragma pack(push, 1)

// The expanded version of the Add Order message has been made available to accommodate larger symbol sizes possible through the ISRA plan.
struct AddOrderExpandedMessage {

    TimeOffset time_offset;
    OrderId order_id;
    SideIndicator side_indicator;
    QuantityLong quantity_long;
    ExpandedSymbol expanded_symbol;
    PriceLong price_long;
    AddFlags add_flags;
    ParticipantId participant_id;
    CustomerIndicator customer_indicator;
    ClientId client_id;
    Reserved5 reserved_5;

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
