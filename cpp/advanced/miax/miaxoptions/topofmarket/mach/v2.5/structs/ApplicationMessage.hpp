#pragma once

#include <cstddef>
#include "../types/MessageType.hpp"

namespace miax::miaxoptions::topofmarket::mach::v2_5 {

namespace mach_topofmarket = ::miax::miaxoptions::topofmarket::mach::v2_5;

#pragma pack(push, 1)

struct application_message {

    mach_topofmarket::message_type message_type;

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
