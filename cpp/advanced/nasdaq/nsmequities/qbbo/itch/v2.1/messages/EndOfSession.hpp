#pragma once

#include <cstdint>

namespace nasdaq::nsmequities::qbbo::itch::v2_1 {

// End Of Session
struct end_of_session {

    static constexpr auto name = "End Of Session";

    // selected when message_count == 65535
    static constexpr auto field = "message_count";
    static constexpr std::uint16_t value = 65535;

    // action properties
    static constexpr auto session = "End";
    static constexpr auto origin = "Exchange";
};

}
