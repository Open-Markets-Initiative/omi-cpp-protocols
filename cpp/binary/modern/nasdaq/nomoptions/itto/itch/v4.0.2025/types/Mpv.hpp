#pragma once

#include <cstddef>

namespace nasdaq::nomoptions::itto::itch::v4_0_2025 {


// Minimum Price Variation for this option. See Notes below for further explanation:
struct Mpv {

    static constexpr auto name = "Mpv";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr Mpv()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit Mpv(const char &value)
     : value{ value } {}

    // get value of Mpv field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
