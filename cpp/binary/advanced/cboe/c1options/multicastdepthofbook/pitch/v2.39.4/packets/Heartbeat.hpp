#pragma once

#include <cstdint>

namespace cboe::c1options::multicastdepthofbook::pitch::v2_39_4 {

// Heartbeat
struct heartbeat {

    static constexpr auto name = "Heartbeat";

    // selected when message_count == 0
    static constexpr auto field = "message_count";
    static constexpr std::uint8_t value = 0;
};

}
