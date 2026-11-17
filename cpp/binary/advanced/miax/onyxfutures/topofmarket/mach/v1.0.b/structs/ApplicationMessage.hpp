// Miax.OnyxFutures.TopOfMarket.Mach.v1.0.b: structs/ApplicationMessage.hpp
#pragma once

#include <cstddef>
#include "../types/MessageType.hpp"

namespace miax::onyxfutures::topofmarket::mach::v1_0_b {

namespace mach_topofmarket = ::miax::onyxfutures::topofmarket::mach::v1_0_b;

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
