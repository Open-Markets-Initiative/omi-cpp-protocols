#pragma once

namespace nasdaq::nsmequities::totalview::itch::v5_0_2026 {

// Logout Request Packet
struct logout_request_packet {

    static constexpr auto name = "Logout Request Packet";

    // selected when client_packet_type == 'O'
    static constexpr auto field = "client_packet_type";
    static constexpr char value = 'O';

    // action properties
    static constexpr auto session = "Logout";
    static constexpr auto origin = "Client";
};

}
