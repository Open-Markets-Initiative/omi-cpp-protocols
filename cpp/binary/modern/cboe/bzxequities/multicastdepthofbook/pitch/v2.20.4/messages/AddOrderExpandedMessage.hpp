// Cboe.BzxEquities.MulticastDepthOfBook.Pitch.v2.20.4: messages/AddOrderExpandedMessage.hpp
#pragma once

#include "../types/TimeOffset.hpp"
#include "../types/OrderId.hpp"
#include "../types/SideIndicator.hpp"
#include "../types/QuantityLong.hpp"
#include "../types/SymbolLong.hpp"
#include "../types/PriceLong.hpp"
#include "../bitfields/AddFlags.hpp"
#include "../types/ParticipantId.hpp"
#include "../structs/MessageHeader.hpp"

namespace cboe::bzxequities::multicastdepthofbook::pitch::v2_20_4 {

#pragma pack(push, 1)

// Add Order message (expanded)
struct AddOrderExpandedMessage {

    TimeOffset time_offset;
    OrderId order_id;
    SideIndicator side_indicator;
    QuantityLong quantity_long;
    SymbolLong symbol_long;
    PriceLong price_long;
    AddFlags add_flags;
    ParticipantId participant_id;

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
