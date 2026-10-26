#pragma once

#include <cstdint>

namespace iex::iexequities::deep::iextp::v1_08 {

// Heartbeat
struct heartbeat {

    static constexpr auto name = "Heartbeat";

    // selected when message_count == 0
    static constexpr auto field = "message_count";
    static constexpr std::uint16_t value = 0;
};

}
