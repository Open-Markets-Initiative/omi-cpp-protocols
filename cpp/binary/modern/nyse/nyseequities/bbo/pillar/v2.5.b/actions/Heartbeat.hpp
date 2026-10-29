#pragma once

#include <cstdint>

namespace nyse::nyseequities::bbo::pillar::v2_5_b {

// Heartbeat
struct Heartbeat {

    static constexpr auto name = "Heartbeat";

    // selected when DeliveryFlag == 1
    static constexpr auto field = "DeliveryFlag";
    static constexpr std::uint8_t value = 1;

    // action properties
    static constexpr auto session = "Heartbeat";
    static constexpr auto origin = "Exchange";
};

}
