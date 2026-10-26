#pragma once

#include <cstddef>
#include <cstdint>

namespace lseg::lse::level2mbo::gtp::v26_2 {

// Turnover of all trades for the day.
struct Turnover {

    static constexpr const char* name = "Turnover";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 4;
    static constexpr double denominator = 10000;
    using type = std::int64_t;

    // default constructor
    constexpr Turnover()
     : value{ 0 } {}

    // constructor for Turnover field
    constexpr explicit Turnover(const std::int64_t value)
     : value{ value } {}

    // get underlying integer of Turnover field
    [[nodiscard]] std::int64_t integer() const {
        return value;
    }

    // decimal value of Turnover field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::int64_t value;
};
}
