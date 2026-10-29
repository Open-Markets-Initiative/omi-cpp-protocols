#pragma once

namespace jnx::jnxequities::pts::ouch::v1_11 {

// Logout Request
struct logout_request {

    static constexpr auto name = "Logout Request";

    // selected when client_packet_type == 'O'
    static constexpr auto field = "client_packet_type";
    static constexpr char value = 'O';

    // action properties
    static constexpr auto session = "Logout";
    static constexpr auto origin = "Client";
};

}
