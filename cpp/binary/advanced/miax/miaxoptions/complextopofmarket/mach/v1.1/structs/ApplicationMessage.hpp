// Miax.MiaxOptions.ComplexTopOfMarket.Mach.v1.1: structs/ApplicationMessage.hpp
#pragma once

#include <cstddef>
#include "../types/MessageType.hpp"

namespace miax::miaxoptions::complextopofmarket::mach::v1_1 {

namespace mach_complextopofmarket = ::miax::miaxoptions::complextopofmarket::mach::v1_1;

#pragma pack(push, 1)

struct application_message {

    mach_complextopofmarket::message_type message_type;

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
