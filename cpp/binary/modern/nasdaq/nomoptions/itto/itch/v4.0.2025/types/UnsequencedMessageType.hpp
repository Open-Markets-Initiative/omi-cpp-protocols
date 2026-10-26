#pragma once

#include <cstddef>

namespace nasdaq::nomoptions::itto::itch::v4_0_2025 {


// Value identifying unsequenced message type
struct UnsequencedMessageType {

    static constexpr auto name = "Unsequenced Message Type";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr UnsequencedMessageType()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit UnsequencedMessageType(const char &value)
     : value{ value } {}

    // get value of UnsequencedMessageType field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
