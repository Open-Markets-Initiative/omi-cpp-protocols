#pragma once

#include <cstddef>
#include <cstdint>

namespace iex::iexequities::tops::iextp::v1_66 {


// Version of transport specification
struct Version {

    static constexpr auto name = "Version";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr Version()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit Version(const std::uint8_t &value)
     : value{ value } {}

    // get value of Version field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
