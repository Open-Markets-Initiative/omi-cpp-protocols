#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace nasdaq::iseoptions::topcomboquotefeed::itch::v1_0 {

// Customer professional quantity on the ask side.
struct AskProCustSize {

    static constexpr const char* name = "Ask Pro Cust Size";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr AskProCustSize()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit AskProCustSize(const std::uint32_t value)
     : value{ std::byteswap(value) } {}

    // get value of AskProCustSize field
    [[nodiscard]] std::uint32_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint32_t value;
};
}
