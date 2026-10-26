#pragma once

namespace nasdaq::nsmequities::totalview::itch::v5_0_2017 {

// End Of Session
struct end_of_session {

    static constexpr auto name = "End Of Session";

    // selected when server_packet_type == 'Z'
    static constexpr auto field = "server_packet_type";
    static constexpr char value = 'Z';

    // action properties
    static constexpr auto session = "End";
    static constexpr auto origin = "Exchange";
};

}
