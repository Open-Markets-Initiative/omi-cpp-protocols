// Miax.PearlEquities.DepthOfMarket.Mach.v1.3.d: messages/RetransmissionRequest.hpp
#pragma once

#include <cstddef>
#include "../structs/EsesmPacketHeader.hpp"
#include "../types/StartSequenceNumber.hpp"
#include "../types/EndSequenceNumber.hpp"

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {

namespace mach_depthofmarket = ::miax::pearlequities::depthofmarket::mach::v1_3_d;

#pragma pack(push, 1)

// Retransmission Request
struct retransmission_request {

    struct fields_type {
        mach_depthofmarket::start_sequence_number start_sequence_number;
        mach_depthofmarket::end_sequence_number end_sequence_number;
    };

    mach_depthofmarket::esesm_packet_header header = {std::uint16_t(sizeof(mach_depthofmarket::esesm_packet_header) + sizeof(fields_type) - 2), esesm_packet_type::enum_type::retransmission_request};

    fields_type fields;

    // parse method
    static retransmission_request* parse(std::byte* buffer) {
        return reinterpret_cast<retransmission_request*>(buffer);
    }

    // parse method const
    static const retransmission_request* parse(const std::byte* buffer) {
        return reinterpret_cast<const retransmission_request*>(buffer);
    }

};

// layout verification
static_assert(offsetof(retransmission_request::fields_type, start_sequence_number) == 0, "unexpected offset of retransmission_request::fields_type::start_sequence_number");
static_assert(offsetof(retransmission_request::fields_type, end_sequence_number) == 8, "unexpected offset of retransmission_request::fields_type::end_sequence_number");
static_assert(sizeof(retransmission_request::fields_type) == 16, "unexpected sizeof retransmission_request::fields_type");
static_assert(sizeof(retransmission_request) == sizeof(mach_depthofmarket::esesm_packet_header) + 16, "unexpected sizeof retransmission_request");

#pragma pack(pop)
}
