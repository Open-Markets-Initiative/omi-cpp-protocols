#pragma once

#include <cstddef>
#include <cstdint>

namespace iex::iexequities::tops::iextp::v1_66 {

// Clearing price at or within the Reference Price Range using orders on the Auction Book
struct ReferencePrice {

    static constexpr const char* name = "Reference Price";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 4;
    static constexpr double denominator = 10000;
    using type = std::int64_t;

    // default constructor
    constexpr ReferencePrice()
     : value{ 0 } {}

    // constructor for ReferencePrice field
    constexpr explicit ReferencePrice(const std::int64_t value)
     : value{ value } {}

    // get underlying integer of ReferencePrice field
    [[nodiscard]] std::int64_t integer() const {
        return value;
    }

    // decimal value of ReferencePrice field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::int64_t value;
};
}
