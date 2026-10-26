#pragma once

#include <cstddef>
#include <cstdint>

namespace iex::iexequities::tops::iextp::v1_56 {

// Aggregate quoted best bid size
struct BidSize {

    static constexpr const char* name = "Bid Size";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr BidSize()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit BidSize(const std::uint32_t value)
     : value{ value } {}

    // get value of BidSize field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
