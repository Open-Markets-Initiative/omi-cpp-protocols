#pragma once

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {

// Trading Session Update
struct trading_session_update {

    static constexpr auto name = "Trading Session Update";

    // selected when esesm_packet_type == 'u'
    static constexpr auto field = "esesm_packet_type";
    static constexpr char value = 'u';
};

}
