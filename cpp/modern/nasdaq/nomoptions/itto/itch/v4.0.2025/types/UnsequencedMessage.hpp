#pragma once

#include <cstddef>

namespace nasdaq::nomoptions::itto::itch::v4_0_2025 {


// The unsequenced (client to server) message carried by the packet, opaque bytes unless an application source dispatches it
struct UnsequencedMessage {

    static constexpr auto name = "Unsequenced Message";
    static constexpr std::size_t size = 0;

    // underlying type
    using type = std::array<std::uint8_t, size>;

    // default constructor
    constexpr UnsequencedMessage()
     : value{} {}

  protected:
    type value;
};
}
