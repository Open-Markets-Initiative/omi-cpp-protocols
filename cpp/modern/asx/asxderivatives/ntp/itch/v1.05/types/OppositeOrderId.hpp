#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace asx::asxderivatives::ntp::itch::v1_05 {

// Public Order Id of the order to be removed from the opposite side of the same Order Book id, as order has traded out.
struct OppositeOrderId {

    static constexpr const char* name = "Opposite Order Id";
    static constexpr std::size_t size =  8;
    using type = std::uint64_t;

    // default constructor
    constexpr OppositeOrderId()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit OppositeOrderId(const std::uint64_t value)
     : value{ std::byteswap(value) } {}

    // get value of OppositeOrderId field
    [[nodiscard]] std::uint64_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint64_t value;
};
}
