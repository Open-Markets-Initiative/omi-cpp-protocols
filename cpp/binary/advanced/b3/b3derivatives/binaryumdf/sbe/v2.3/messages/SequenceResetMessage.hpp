// B3.B3Derivatives.BinaryUmdf.Sbe.v2.3: messages/SequenceResetMessage.hpp
#pragma once

#include <cstddef>
#include "../structs/FramingHeader.hpp"
#include "../structs/MessageHeader.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v2_3 {

namespace sbe_binaryumdf = ::b3::b3derivatives::binaryumdf::sbe::v2_3;

#pragma pack(push, 1)

// Sequence Reset Message
struct sequence_reset_message {

    sbe_binaryumdf::framing_header header = {std::uint16_t(sizeof(sbe_binaryumdf::framing_header) + sizeof(sbe_binaryumdf::message_header)), encoding_type(60240)};
    sbe_binaryumdf::message_header message_header = {{}, template_id::enum_type::sequence_reset_1_message, schema_id(2), version(17)};

    // parse method
    static sequence_reset_message* parse(std::byte* buffer) {
        return reinterpret_cast<sequence_reset_message*>(buffer);
    }

    // parse method const
    static const sequence_reset_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const sequence_reset_message*>(buffer);
    }

};

// layout verification
static_assert(sizeof(sequence_reset_message) == sizeof(sbe_binaryumdf::framing_header) + sizeof(sbe_binaryumdf::message_header) + 0, "unexpected sizeof sequence_reset_message");

#pragma pack(pop)
}
