#pragma once

#include <cstddef>
#include "../structs/SesmPacketHeader.hpp"
#include "../structs/SbeGroupSupport.hpp"
#include "../types/SequenceNumber.hpp"
#include "../types/UnsequencedMessageType.hpp"

namespace miax::miaxoptions::topofmarket::mach::v2_5 {

namespace mach_topofmarket = ::miax::miaxoptions::topofmarket::mach::v2_5;


#pragma pack(push, 1)

// Refresh Response Message
struct refresh_response_message {

    struct fields_type {
        mach_topofmarket::sequence_number sequence_number;
    };

    mach_topofmarket::sesm_packet_header header = {std::uint16_t(sizeof(mach_topofmarket::sesm_packet_header) + sizeof(fields_type) + sizeof(mach_topofmarket::unsequenced_message_type) - 2), sesm_packet_type::enum_type::unsequenced_data_packet};
    mach_topofmarket::unsequenced_message_type unsequenced_message_type = mach_topofmarket::unsequenced_message_type::enum_type::refresh_response_message;

    static constexpr std::size_t max_message_size = 1280;
    static constexpr std::size_t tail_capacity = max_message_size - sizeof(mach_topofmarket::sesm_packet_header) - sizeof(fields_type) - sizeof(mach_topofmarket::unsequenced_message_type);

    fields_type fields;
    std::byte tail[tail_capacity];

    // tail buffer accessors
    const std::byte* tail_begin() const { return tail; }
    const std::byte* tail_end() const {
        auto sz = header.sesm_packet_length.get().value();
        return (sz + 2) == sizeof(mach_topofmarket::sesm_packet_header) + sizeof(fields_type) + sizeof(mach_topofmarket::unsequenced_message_type)
            ? tail + tail_capacity
            : tail + ((sz + 2) - sizeof(mach_topofmarket::sesm_packet_header) - sizeof(fields_type) - sizeof(mach_topofmarket::unsequenced_message_type));
    }

    // sequential access to variable-length regions
    external_var_data application_message() const {
        return { tail_begin(), static_cast<std::size_t>(header.sesm_packet_length.get().value() - 12), tail_end() };
    }


    // parse method
    static refresh_response_message* parse(std::byte* buffer) {
        return reinterpret_cast<refresh_response_message*>(buffer);
    }

    // parse method const
    static const refresh_response_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const refresh_response_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(refresh_response_message::fields_type, sequence_number) == 0, "unexpected offset of refresh_response_message::fields_type::sequence_number");
static_assert(sizeof(refresh_response_message::fields_type) == 8, "unexpected sizeof refresh_response_message::fields_type");

#pragma pack(pop)
}

#include "details/RefreshResponseMessageWriter.hpp"
#include "details/RefreshResponseMessageReader.hpp"
