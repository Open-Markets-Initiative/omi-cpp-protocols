#pragma once

#include "../types/ControlMessageType.hpp"

namespace siac::cts::output::cta::v2_11_b {

#pragma pack(push, 1)

struct ControlMessage {

    ControlMessageType control_message_type;

    // parse method
    static ControlMessage* parse(std::byte* buffer) {
        return reinterpret_cast<ControlMessage*>(buffer);
    }

    // parse method const
    static const ControlMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const ControlMessage*>(buffer);
    }
};

#pragma pack(pop)
}
