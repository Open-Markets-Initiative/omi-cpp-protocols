#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/MessageIndicator.hpp"
#include "../types/TransactionId.hpp"
#include "../types/ParticipantReferenceNumber.hpp"
#include "../types/ControlMessageType.hpp"

namespace siac::opra::output::obi::v6_2 {

namespace obi_output = ::siac::opra::output::obi::v6_2;

#pragma pack(push, 1)

// Control Message
struct control_message {

    struct fields_type {
        obi_output::message_indicator message_indicator;
        obi_output::transaction_id transaction_id;
        obi_output::participant_reference_number participant_reference_number;
    };

    obi_output::message_header header = {{}, message_category::enum_type::control};
    obi_output::control_message_type control_message_type = obi_output::control_message_type::enum_type::start_of_day;

    fields_type fields;

    // parse method
    static control_message* parse(std::byte* buffer) {
        return reinterpret_cast<control_message*>(buffer);
    }

    // parse method const
    static const control_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const control_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(control_message::fields_type, message_indicator) == 0, "unexpected offset of control_message::fields_type::message_indicator");
static_assert(offsetof(control_message::fields_type, transaction_id) == 1, "unexpected offset of control_message::fields_type::transaction_id");
static_assert(offsetof(control_message::fields_type, participant_reference_number) == 5, "unexpected offset of control_message::fields_type::participant_reference_number");
static_assert(sizeof(control_message::fields_type) == 9, "unexpected sizeof control_message::fields_type");
static_assert(sizeof(control_message) == sizeof(obi_output::message_header) + sizeof(obi_output::control_message_type) + 9, "unexpected sizeof control_message");

#pragma pack(pop)
}
