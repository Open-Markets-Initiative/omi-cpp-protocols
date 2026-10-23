#pragma once

#include <cstdint>

namespace nasdaq::nomoptions::itto::itch::v4_0_2025 {

// Heartbeat
struct Heartbeat {

    static constexpr auto name = "Heartbeat";

    // selected when MessageCount == 0
    static constexpr auto field = "MessageCount";
    static constexpr std::uint16_t value = 0;

    // action properties
    static constexpr auto session = "Heartbeat";
    static constexpr auto origin = "Exchange";
};

}
