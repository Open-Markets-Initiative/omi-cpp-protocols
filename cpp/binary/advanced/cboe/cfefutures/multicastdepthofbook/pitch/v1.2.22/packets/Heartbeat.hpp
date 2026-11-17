// Cboe.CfeFutures.MulticastDepthOfBook.Pitch.v1.2.22: packets/Heartbeat.hpp
#pragma once

#include <cstdint>

namespace cboe::cfefutures::multicastdepthofbook::pitch::v1_2_22 {

// Heartbeat
struct heartbeat {

    static constexpr auto name = "Heartbeat";

    // selected when message_count == 0
    static constexpr auto field = "message_count";
    static constexpr std::uint8_t value = 0;
};

}
