// Miax.PearlEquities.DepthOfMarket.Mach.v1.3.d: messages/RetransmissionRequest.hpp
#pragma once

#include "../types/StartSequenceNumber.hpp"
#include "../types/EndSequenceNumber.hpp"
#include "../structs/EsesmPacketHeader.hpp"

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {

#pragma pack(push, 1)

// The ESesM client uses this packet to request a retransmission server to retransmit a range of packets
struct RetransmissionRequest {

    StartSequenceNumber start_sequence_number;
    EndSequenceNumber end_sequence_number;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'a';

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
