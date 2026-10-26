#pragma once

#include <cstddef>
#include <cstdint>

namespace iex::iexequities::tops::iextp::v1_64 {

// Official opening or closing price, as specified
struct OfficialPrice {

    static constexpr const char* name = "Official Price";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 4;
    static constexpr double denominator = 10000;
    using type = std::int64_t;

    // default constructor
    constexpr OfficialPrice()
     : value{ 0 } {}

    // constructor for OfficialPrice field
    constexpr explicit OfficialPrice(const std::int64_t value)
     : value{ value } {}

    // get underlying integer of OfficialPrice field
    [[nodiscard]] std::int64_t integer() const {
        return value;
    }

    // decimal value of OfficialPrice field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::int64_t value;
};
}
