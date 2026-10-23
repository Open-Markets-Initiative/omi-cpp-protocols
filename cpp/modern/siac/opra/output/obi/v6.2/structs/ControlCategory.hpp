#pragma once

#include "../types/ControlMessageType.hpp"

namespace siac::opra::output::obi::v6_2 {

#pragma pack(push, 1)

struct ControlCategory {

    ControlMessageType control_message_type;

    // parse method
    static ControlCategory* parse(std::byte* buffer) {
        return reinterpret_cast<ControlCategory*>(buffer);
    }

    // parse method const
    static const ControlCategory* parse(const std::byte* buffer) {
        return reinterpret_cast<const ControlCategory*>(buffer);
    }
};

#pragma pack(pop)
}
