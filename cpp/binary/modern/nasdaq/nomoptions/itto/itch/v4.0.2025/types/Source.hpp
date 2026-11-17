// Nasdaq.NomOptions.Itto.Itch.v4.0.2025: types/Source.hpp
#pragma once

#include <cstddef>
#include <cstdint>

namespace nasdaq::nomoptions::itto::itch::v4_0_2025 {


// Identifies the source of the Option, valid for the trading day
struct Source {

    static constexpr auto name = "Source";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr Source()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit Source(const std::uint8_t &value)
     : value{ value } {}

    // get value of Source field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
