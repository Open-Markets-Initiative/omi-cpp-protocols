#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace siac::cts::output::cta::v2_10 {

// The Bid Index Value represents the value of the index’s calculation formula using the current Bid values of the component securities.
struct BidIndexValue {

    static constexpr const char* name = "Bid Index Value";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 6;
    static constexpr double denominator = 1000000;
    using type = std::int64_t;

    // default constructor
    constexpr BidIndexValue()
     : value{ 0 } {}

    // constructor for BidIndexValue field
    constexpr explicit BidIndexValue(const std::int64_t value)
     : value{ std::byteswap(value) } {}

    // get underlying integer of BidIndexValue field
    [[nodiscard]] std::int64_t integer() const {
        return std::byteswap(value);
    }

    // decimal value of BidIndexValue field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::int64_t value;
};
}
