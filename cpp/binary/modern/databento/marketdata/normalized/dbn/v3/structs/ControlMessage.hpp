#pragma once

#include "../types/ControlFields.hpp"

namespace databento::marketdata::normalized::dbn::v3 {

#pragma pack(push, 1)

struct ControlMessage {

    ControlFields control_fields;

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
