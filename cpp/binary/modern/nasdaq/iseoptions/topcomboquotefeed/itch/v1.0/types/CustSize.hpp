#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace nasdaq::iseoptions::topcomboquotefeed::itch::v1_0 {

// Customer Quantity on the bid or ask side.
struct CustSize {

    static constexpr const char* name = "Cust Size";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr CustSize()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit CustSize(const std::uint32_t value)
     : value{ std::byteswap(value) } {}

    // get value of CustSize field
    [[nodiscard]] std::uint32_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint32_t value;
};
}
