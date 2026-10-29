#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace nasdaq::iseoptions::topcomboquotefeed::itch::v1_0 {

// Customer professional quantity on the bid or ask side.
struct ProCustSize {

    static constexpr const char* name = "Pro Cust Size";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr ProCustSize()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit ProCustSize(const std::uint32_t value)
     : value{ std::byteswap(value) } {}

    // get value of ProCustSize field
    [[nodiscard]] std::uint32_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint32_t value;
};
}
