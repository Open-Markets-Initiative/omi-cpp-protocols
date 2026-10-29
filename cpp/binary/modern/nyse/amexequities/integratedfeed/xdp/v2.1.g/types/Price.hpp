#pragma once

#include <cstddef>
#include <cstdint>

namespace nyse::amexequities::integratedfeed::xdp::v2_1_g {

// The order price. Use with the Price Scale from the symbol-mapping index.
struct Price {

    static constexpr const char* name = "Price";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr Price()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit Price(const std::uint32_t value)
     : value{ value } {}

    // get value of Price field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
