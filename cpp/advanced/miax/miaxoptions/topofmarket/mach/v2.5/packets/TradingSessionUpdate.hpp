#pragma once

namespace miax::miaxoptions::topofmarket::mach::v2_5 {

// Trading Session Update
struct trading_session_update {

    static constexpr auto name = "Trading Session Update";

    // selected when sesm_packet_type == 'u'
    static constexpr auto field = "sesm_packet_type";
    static constexpr char value = 'u';
};

}
