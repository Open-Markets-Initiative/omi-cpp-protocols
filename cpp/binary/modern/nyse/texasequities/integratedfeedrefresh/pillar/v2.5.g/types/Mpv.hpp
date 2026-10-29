#pragma once

#include <cstddef>
#include <cstdint>

namespace nyse::texasequities::integratedfeedrefresh::pillar::v2_5_g {

// The minimum increment for a trade price, in 100ths of a cent. Typically 1, or $0.0001, but for some Tick Pilot stocks, can be 500, or $0.05.
struct Mpv {

    static constexpr const char* name = "Mpv";
    static constexpr std::size_t size =  2;
    using type = std::uint16_t;

    // default constructor
    constexpr Mpv()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit Mpv(const std::uint16_t value)
     : value{ value } {}

    // get value of Mpv field
    [[nodiscard]] std::uint16_t get() const {
        return value;
    }

  protected:
    std::uint16_t value;
};
}
