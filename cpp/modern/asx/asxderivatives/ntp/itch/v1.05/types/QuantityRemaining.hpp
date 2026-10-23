#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace asx::asxderivatives::ntp::itch::v1_05 {

// Volume remaining on Order after matching, if 0, order has traded out and should be deleted.
struct QuantityRemaining {

    static constexpr const char* name = "Quantity Remaining";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr QuantityRemaining()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit QuantityRemaining(const std::uint32_t value)
     : value{ std::byteswap(value) } {}

    // get value of QuantityRemaining field
    [[nodiscard]] std::uint32_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint32_t value;
};
}
