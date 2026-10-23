#pragma once

#include <cstddef>
#include "../types/SequenceNumber.hpp"
#include "../types/PacketLength.hpp"
#include "../types/PacketType.hpp"
#include "../types/SessionNumber.hpp"

namespace miax::miaxoptions::topofmarket::mach::v2_5 {

namespace mach_topofmarket = ::miax::miaxoptions::topofmarket::mach::v2_5;

#pragma pack(push, 1)

struct mach_message {

    mach_topofmarket::sequence_number sequence_number;
    mach_topofmarket::packet_length packet_length;
    mach_topofmarket::packet_type packet_type;
    mach_topofmarket::session_number session_number;

    // parse method
    static mach_message* parse(std::byte* buffer) {
        return reinterpret_cast<mach_message*>(buffer);
    }

    // parse method const
    static const mach_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const mach_message*>(buffer);
    }
};

#pragma pack(pop)
}
