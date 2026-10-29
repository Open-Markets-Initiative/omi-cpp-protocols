#pragma once

#include <cstdint>

namespace cboe::c1options::complex::pitch::v2_1_18 {

// Heartbeat
struct heartbeat {

    static constexpr auto name = "Heartbeat";

    // selected when message_count == 0
    static constexpr auto field = "message_count";
    static constexpr std::uint8_t value = 0;
};

}
