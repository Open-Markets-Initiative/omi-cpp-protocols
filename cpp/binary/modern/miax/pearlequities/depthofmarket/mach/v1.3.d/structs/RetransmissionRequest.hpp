#pragma once

#include "../types/StartSequenceNumber.hpp"
#include "../types/EndSequenceNumber.hpp"

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {

#pragma pack(push, 1)

struct RetransmissionRequest {

    StartSequenceNumber start_sequence_number;
    EndSequenceNumber end_sequence_number;

    // parse method
    static RetransmissionRequest* parse(std::byte* buffer) {
        return reinterpret_cast<RetransmissionRequest*>(buffer);
    }

    // parse method const
    static const RetransmissionRequest* parse(const std::byte* buffer) {
        return reinterpret_cast<const RetransmissionRequest*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const RetransmissionRequest* parse(const EsesmPacketHeader* header) {
        return reinterpret_cast<const RetransmissionRequest*>(reinterpret_cast<const std::byte*>(header) + sizeof(EsesmPacketHeader));
    }
};

#pragma pack(pop)
}
