#pragma once

#include <cstdint>

namespace miax::miaxoptions::topofmarket::mach::v2_5 {

// End Of Session
struct end_of_session {

    static constexpr auto name = "End Of Session";

    // selected when packet_type == 2
    static constexpr auto field = "packet_type";
    static constexpr std::uint8_t value = 2;
};

}
