#pragma once

#include <cstddef>
#include <cstdint>

namespace nyse::amexequities::integratedfeed::xdp::v2_1_g {

// Default value is 0
struct Price1 {

    static constexpr const char* name = "Price 1";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr Price1()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit Price1(const std::uint32_t value)
     : value{ value } {}

    // get value of Price1 field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
