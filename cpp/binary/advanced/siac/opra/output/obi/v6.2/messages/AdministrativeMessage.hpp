#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../structs/SbeGroupSupport.hpp"
#include "../types/MessageIndicator.hpp"
#include "../types/TransactionId.hpp"
#include "../types/ParticipantReferenceNumber.hpp"
#include "../types/MessageDataLength.hpp"
#include "../types/AdministrativeMessageType.hpp"

namespace siac::opra::output::obi::v6_2 {

namespace obi_output = ::siac::opra::output::obi::v6_2;


#pragma pack(push, 1)

// Administrative Message
struct administrative_message {

    struct fields_type {
        obi_output::message_indicator message_indicator;
        obi_output::transaction_id transaction_id;
        obi_output::participant_reference_number participant_reference_number;
        obi_output::message_data_length message_data_length;
    };

    obi_output::message_header header = {{}, message_category::enum_type::administrative};
    obi_output::administrative_message_type administrative_message_type = obi_output::administrative_message_type::enum_type::administrative;

    static constexpr std::size_t max_message_size = 1280;
    static constexpr std::size_t tail_capacity = max_message_size - sizeof(obi_output::message_header) - sizeof(fields_type) - sizeof(obi_output::administrative_message_type);

    fields_type fields;
    std::byte tail[tail_capacity];

    // tail buffer accessors
    const std::byte* tail_begin() const { return tail; }
    const std::byte* tail_end() const { return tail + tail_capacity; }

    // sequential access to variable-length regions
    external_var_data message_data() const {
        return { tail_begin(), fields.message_data_length.get().value(), tail_end() };
    }


    // parse method
    static administrative_message* parse(std::byte* buffer) {
        return reinterpret_cast<administrative_message*>(buffer);
    }

    // parse method const
    static const administrative_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const administrative_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(administrative_message::fields_type, message_indicator) == 0, "unexpected offset of administrative_message::fields_type::message_indicator");
static_assert(offsetof(administrative_message::fields_type, transaction_id) == 1, "unexpected offset of administrative_message::fields_type::transaction_id");
static_assert(offsetof(administrative_message::fields_type, participant_reference_number) == 5, "unexpected offset of administrative_message::fields_type::participant_reference_number");
static_assert(offsetof(administrative_message::fields_type, message_data_length) == 9, "unexpected offset of administrative_message::fields_type::message_data_length");
static_assert(sizeof(administrative_message::fields_type) == 11, "unexpected sizeof administrative_message::fields_type");

#pragma pack(pop)
}
