#pragma once

#include <cstddef>
#include <cstdint>

namespace tmx::tsx::quantumfeedlevel2::xmt::v2_10 {


// Message version number
struct MsgVersion {

    static constexpr auto name = "Msg Version";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr MsgVersion()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit MsgVersion(const std::uint8_t &value)
     : value{ value } {}

    // get value of MsgVersion field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
