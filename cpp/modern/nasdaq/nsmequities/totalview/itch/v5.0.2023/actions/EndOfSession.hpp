#pragma once

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

// End Of Session
struct EndOfSession {

    static constexpr auto name = "End Of Session";

    // selected when ServerPacketType == 'Z'
    static constexpr auto field = "ServerPacketType";
    static constexpr char value = 'Z';

    // action properties
    static constexpr auto session = "End";
    static constexpr auto origin = "Exchange";
};

}
