#pragma once

#include <cstdint>

namespace nyse::texasequities::integratedfeedrefresh::pillar::v2_5_g {

// Heartbeat
struct heartbeat {

    static constexpr auto name = "Heartbeat";

    // selected when delivery_flag == 1
    static constexpr auto field = "delivery_flag";
    static constexpr std::uint8_t value = 1;

    // action properties
    static constexpr auto session = "Heartbeat";
    static constexpr auto origin = "Exchange";
};

}
