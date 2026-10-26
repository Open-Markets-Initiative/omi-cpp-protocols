#pragma once

#include <cstddef>
#include <cstdint>

namespace iex::iexequities::tops::iextp::v1_56 {

// Best quoted bid price
struct BidPrice {

    static constexpr const char* name = "Bid Price";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 4;
    static constexpr double denominator = 10000;
    using type = std::int64_t;

    // default constructor
    constexpr BidPrice()
     : value{ 0 } {}

    // constructor for BidPrice field
    constexpr explicit BidPrice(const std::int64_t value)
     : value{ value } {}

    // get underlying integer of BidPrice field
    [[nodiscard]] std::int64_t integer() const {
        return value;
    }

    // decimal value of BidPrice field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::int64_t value;
};
}
