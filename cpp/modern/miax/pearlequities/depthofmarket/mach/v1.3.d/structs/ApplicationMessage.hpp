#pragma once

#include "../types/MessageType.hpp"

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {

#pragma pack(push, 1)

struct ApplicationMessage {

    MessageType message_type;

    // parse method
    static ApplicationMessage* parse(std::byte* buffer) {
        return reinterpret_cast<ApplicationMessage*>(buffer);
    }

    // parse method const
    static const ApplicationMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const ApplicationMessage*>(buffer);
    }
};

#pragma pack(pop)
}
