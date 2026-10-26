#pragma once

#include "../types/OpenInterestMessageType.hpp"

namespace siac::opra::output::obi::v6_2 {

#pragma pack(push, 1)

struct OpenInterestCategory {

    OpenInterestMessageType open_interest_message_type;

    // parse method
    static OpenInterestCategory* parse(std::byte* buffer) {
        return reinterpret_cast<OpenInterestCategory*>(buffer);
    }

    // parse method const
    static const OpenInterestCategory* parse(const std::byte* buffer) {
        return reinterpret_cast<const OpenInterestCategory*>(buffer);
    }
};

#pragma pack(pop)
}
