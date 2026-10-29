#pragma once

#include <cstddef>

namespace tmx::tsx::quantumfeedlevel2::xmt::v2_10 {


// Protocol Name
struct ProtocolName {

    static constexpr auto name = "Protocol Name";
    static constexpr std::size_t size = 1;
    using type = char;
static const type static_value = 'X';

    // default constructor
    constexpr ProtocolName()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit ProtocolName(const char &value)
     : value{ value } {}

    // get value of ProtocolName field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
