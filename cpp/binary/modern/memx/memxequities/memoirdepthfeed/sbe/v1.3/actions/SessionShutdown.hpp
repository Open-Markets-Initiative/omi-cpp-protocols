#pragma once

#include <cstdint>

namespace memx::memxequities::memoirdepthfeed::sbe::v1_3 {

// Session Shutdown
struct SessionShutdown {

    static constexpr auto name = "Session Shutdown";

    // selected when MessageType == 1
    static constexpr auto field = "MessageType";
    static constexpr std::uint8_t value = 1;

    // action properties
    static constexpr auto session = "End";
    static constexpr auto origin = "Exchange";
};

}
