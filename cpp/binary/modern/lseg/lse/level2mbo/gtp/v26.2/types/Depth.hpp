#pragma once

#include <cstddef>
#include <cstdint>

namespace lseg::lse::level2mbo::gtp::v26_2 {


// Total number of orders disseminated including this one, on this side of the book as indicated by Side field.
struct Depth {

    static constexpr auto name = "Depth";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr Depth()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit Depth(const std::uint8_t &value)
     : value{ value } {}

    // get value of Depth field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
