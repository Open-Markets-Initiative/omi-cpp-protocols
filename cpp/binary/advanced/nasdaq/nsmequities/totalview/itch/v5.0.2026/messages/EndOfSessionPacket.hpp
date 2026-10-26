#pragma once

namespace nasdaq::nsmequities::totalview::itch::v5_0_2026 {

// End Of Session Packet
struct end_of_session_packet {

    static constexpr auto name = "End Of Session Packet";

    // selected when server_packet_type == 'Z'
    static constexpr auto field = "server_packet_type";
    static constexpr char value = 'Z';

    // action properties
    static constexpr auto session = "End";
    static constexpr auto origin = "Exchange";
};

}
