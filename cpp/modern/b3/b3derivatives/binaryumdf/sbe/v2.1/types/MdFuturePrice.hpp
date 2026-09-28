#pragma once

#include <cstddef>
#include <cstdint>

namespace b3::b3derivatives::binaryumdf::sbe::v2_1 {

// mDEntryPx
struct MdFuturePrice {

    static constexpr const char* name = "Md Future Price";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 4;
    static constexpr double denominator = 10000;
    using type = std::int64_t;

    // default constructor
    constexpr MdFuturePrice()
     : value{ 0 } {}

    // constructor for MdFuturePrice field
    constexpr explicit MdFuturePrice(const std::int64_t value)
     : value{ value } {}

    // get underlying integer of MdFuturePrice field
    [[nodiscard]] std::int64_t integer() const {
        return value;
    }

    // decimal value of MdFuturePrice field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::int64_t value;
};
}
