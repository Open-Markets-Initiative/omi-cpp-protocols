#pragma once

#include <cstdint>

namespace memx::memxequities::memoirdepthfeed::sbe::v1_3 {

// Heartbeat
struct Heartbeat {

    static constexpr auto name = "Heartbeat";

    // selected when MessageType == 0
    static constexpr auto field = "MessageType";
    static constexpr std::uint8_t value = 0;

    // action properties
    static constexpr auto session = "Heartbeat";
    static constexpr auto origin = "Exchange";
};

}
