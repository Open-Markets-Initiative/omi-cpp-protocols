#pragma once

#include <cstdint>

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

// End Of Session
struct EndOfSession {

    static constexpr auto name = "End Of Session";

    // selected when MessageCount == 65535
    static constexpr auto field = "MessageCount";
    static constexpr std::uint16_t value = 65535;

    // action properties
    static constexpr auto session = "End";
    static constexpr auto origin = "Exchange";
};

}
