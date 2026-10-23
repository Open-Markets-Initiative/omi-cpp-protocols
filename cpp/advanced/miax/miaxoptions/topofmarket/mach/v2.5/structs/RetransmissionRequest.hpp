#pragma once

#include <cstddef>
#include "../types/StartSequenceNumber.hpp"
#include "../types/EndSequenceNumber.hpp"

namespace miax::miaxoptions::topofmarket::mach::v2_5 {

namespace mach_topofmarket = ::miax::miaxoptions::topofmarket::mach::v2_5;

#pragma pack(push, 1)

struct retransmission_request {

    mach_topofmarket::start_sequence_number start_sequence_number;
    mach_topofmarket::end_sequence_number end_sequence_number;

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
static_assert(offsetof(retransmission_request, start_sequence_number) == 0, "unexpected offset of retransmission_request::start_sequence_number");
static_assert(offsetof(retransmission_request, end_sequence_number) == 8, "unexpected offset of retransmission_request::end_sequence_number");
static_assert(sizeof(retransmission_request) == 16, "unexpected sizeof retransmission_request");

#pragma pack(pop)
}
