#pragma once

#include <cstddef>
#include <cstdint>

namespace nyse::amexequities::integratedfeed::xdp::v2_1_g {


// The unique ID for this NYSE feed listed in the feed’s client specification.
struct ProductId {

    static constexpr auto name = "Product Id";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr ProductId()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit ProductId(const std::uint8_t &value)
     : value{ value } {}

    // get value of ProductId field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
