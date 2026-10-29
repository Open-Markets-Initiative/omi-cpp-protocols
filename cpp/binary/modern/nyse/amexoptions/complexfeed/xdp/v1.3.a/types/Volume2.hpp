#pragma once

#include <cstddef>
#include <cstdint>

namespace nyse::amexoptions::complexfeed::xdp::v1_3_a {

// Total quantity
struct Volume2 {

    static constexpr const char* name = "Volume 2";
    static constexpr std::size_t size =  2;
    using type = std::uint16_t;

    // default constructor
    constexpr Volume2()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit Volume2(const std::uint16_t value)
     : value{ value } {}

    // get value of Volume2 field
    [[nodiscard]] std::uint16_t get() const {
        return value;
    }

  protected:
    std::uint16_t value;
};
}
