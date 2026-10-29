#pragma once

#include <cstddef>
#include "../types/AdministrativeMessageType.hpp"

namespace siac::cts::output::cta::v2_9 {

namespace cta_output = ::siac::cts::output::cta::v2_9;

#pragma pack(push, 1)

struct administrative_message {

    cta_output::administrative_message_type administrative_message_type;

    // parse method
    static administrative_message* parse(std::byte* buffer) {
        return reinterpret_cast<administrative_message*>(buffer);
    }

    // parse method const
    static const administrative_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const administrative_message*>(buffer);
    }
};

#pragma pack(pop)
}
