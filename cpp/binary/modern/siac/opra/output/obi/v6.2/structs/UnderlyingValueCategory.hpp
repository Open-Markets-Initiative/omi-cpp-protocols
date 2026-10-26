#pragma once

#include "../types/UnderlyingValueMessageType.hpp"

namespace siac::opra::output::obi::v6_2 {

#pragma pack(push, 1)

struct UnderlyingValueCategory {

    UnderlyingValueMessageType underlying_value_message_type;

    // parse method
    static UnderlyingValueCategory* parse(std::byte* buffer) {
        return reinterpret_cast<UnderlyingValueCategory*>(buffer);
    }

    // parse method const
    static const UnderlyingValueCategory* parse(const std::byte* buffer) {
        return reinterpret_cast<const UnderlyingValueCategory*>(buffer);
    }
};

#pragma pack(pop)
}
