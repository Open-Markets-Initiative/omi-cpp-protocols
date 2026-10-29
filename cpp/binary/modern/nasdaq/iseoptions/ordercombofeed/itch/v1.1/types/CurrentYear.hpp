#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace nasdaq::iseoptions::ordercombofeed::itch::v1_1 {

// The current calendar year (example: 2016).
struct CurrentYear {

    static constexpr const char* name = "Current Year";
    static constexpr std::size_t size =  2;
    using type = std::uint16_t;

    // default constructor
    constexpr CurrentYear()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit CurrentYear(const std::uint16_t value)
     : value{ std::byteswap(value) } {}

    // get value of CurrentYear field
    [[nodiscard]] std::uint16_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint16_t value;
};
}
