#pragma once

#include <cstdint>

namespace memx::memxequities::memoirdepthfeed::sbe::v1_3 {

// Heartbeat
struct heartbeat {

    static constexpr auto name = "Heartbeat";

    // selected when message_type == 0
    static constexpr auto field = "message_type";
    static constexpr std::uint8_t value = 0;

    // action properties
    static constexpr auto session = "Heartbeat";
    static constexpr auto origin = "Exchange";
};

}
