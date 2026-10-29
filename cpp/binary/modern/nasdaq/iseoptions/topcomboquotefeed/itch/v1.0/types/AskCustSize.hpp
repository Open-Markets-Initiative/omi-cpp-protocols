#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace nasdaq::iseoptions::topcomboquotefeed::itch::v1_0 {

// Customer quantity on the ask side.
struct AskCustSize {

    static constexpr const char* name = "Ask Cust Size";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr AskCustSize()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit AskCustSize(const std::uint32_t value)
     : value{ std::byteswap(value) } {}

    // get value of AskCustSize field
    [[nodiscard]] std::uint32_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint32_t value;
};
}
