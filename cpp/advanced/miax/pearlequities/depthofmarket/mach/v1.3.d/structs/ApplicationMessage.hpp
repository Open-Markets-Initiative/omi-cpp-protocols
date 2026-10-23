#pragma once

#include <cstddef>
#include "../types/MessageType.hpp"

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {

namespace mach_depthofmarket = ::miax::pearlequities::depthofmarket::mach::v1_3_d;

#pragma pack(push, 1)

struct application_message {

    mach_depthofmarket::message_type message_type;

    // parse method
    static application_message* parse(std::byte* buffer) {
        return reinterpret_cast<application_message*>(buffer);
    }

    // parse method const
    static const application_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const application_message*>(buffer);
    }
};

#pragma pack(pop)
}
