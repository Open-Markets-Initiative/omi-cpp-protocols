#pragma once

#include <cstdint>

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {

// End Of Session
struct end_of_session {

    static constexpr auto name = "End Of Session";

    // selected when mach_packet_type == 2
    static constexpr auto field = "mach_packet_type";
    static constexpr std::uint8_t value = 2;
};

}
