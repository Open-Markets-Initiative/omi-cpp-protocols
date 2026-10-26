#pragma once

#include <cstdint>

namespace memx::memxequities::memoirdepthfeed::sbe::v1_3 {

// Session Shutdown
struct session_shutdown {

    static constexpr auto name = "Session Shutdown";

    // selected when message_type == 1
    static constexpr auto field = "message_type";
    static constexpr std::uint8_t value = 1;

    // action properties
    static constexpr auto session = "End";
    static constexpr auto origin = "Exchange";
};

}
