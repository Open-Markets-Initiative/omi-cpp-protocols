#pragma once

#include <cstddef>
#include <cstdint>

namespace lseg::lse::level2mbo::gtp::v26_2 {

// The value of price type statistics. If the Opening or Closing Price is cleared manually by the venue, '-1' will be stamped.
struct StatisticPrice {

    static constexpr const char* name = "Statistic Price";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 8;
    static constexpr double denominator = 100000000;
    using type = std::int64_t;

    // default constructor
    constexpr StatisticPrice()
     : value{ 0 } {}

    // constructor for StatisticPrice field
    constexpr explicit StatisticPrice(const std::int64_t value)
     : value{ value } {}

    // get underlying integer of StatisticPrice field
    [[nodiscard]] std::int64_t integer() const {
        return value;
    }

    // decimal value of StatisticPrice field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::int64_t value;
};
}
