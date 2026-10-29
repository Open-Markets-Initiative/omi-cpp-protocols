#pragma once

#include "../types/TimeOffset.hpp"
#include "../types/OrderId.hpp"
#include "../types/SideIndicator.hpp"
#include "../types/Quantity.hpp"
#include "../types/ComplexInstrumentId8.hpp"
#include "../types/Price.hpp"
#include "../types/Reserved1.hpp"
#include "../types/ParticipantId.hpp"
#include "../types/CustomerIndicator.hpp"
#include "../types/ClientId.hpp"
#include "../structs/MessageHeader.hpp"

namespace cboe::c1options::complex::pitch::v2_1_18 {

#pragma pack(push, 1)

// An Add Order message represents a newly accepted visible order on the Cboe book. Expanded version accommodates larger symbol sizes possible through the ISRA plan.
struct AddOrderExpandedMessage {

    TimeOffset time_offset;
    OrderId order_id;
    SideIndicator side_indicator;
    Quantity quantity;
    ComplexInstrumentId8 complex_instrument_id_8;
    Price price;
    Reserved1 reserved_1;
    ParticipantId participant_id;
    CustomerIndicator customer_indicator;
    ClientId client_id;

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
