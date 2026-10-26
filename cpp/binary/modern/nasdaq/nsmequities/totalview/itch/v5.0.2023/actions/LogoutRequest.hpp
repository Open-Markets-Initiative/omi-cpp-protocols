#pragma once

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

// Logout Request
struct LogoutRequest {

    static constexpr auto name = "Logout Request";

    // selected when ClientPacketType == 'O'
    static constexpr auto field = "ClientPacketType";
    static constexpr char value = 'O';

    // action properties
    static constexpr auto session = "Logout";
    static constexpr auto origin = "Client";
};

}
