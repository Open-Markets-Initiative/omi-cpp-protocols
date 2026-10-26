#pragma once

namespace nasdaq::nsmequities::totalview::itch::v5_0_2026 {

// End Of Session Packet
struct EndOfSessionPacket {

    static constexpr auto name = "End Of Session Packet";

    // selected when ServerPacketType == 'Z'
    static constexpr auto field = "ServerPacketType";
    static constexpr char value = 'Z';

    // action properties
    static constexpr auto session = "End";
    static constexpr auto origin = "Exchange";
};

}
