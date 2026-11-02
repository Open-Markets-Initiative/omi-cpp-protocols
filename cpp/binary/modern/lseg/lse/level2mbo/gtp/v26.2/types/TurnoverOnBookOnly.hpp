#pragma once

#include <cstddef>
#include <cstdint>

namespace lseg::lse::level2mbo::gtp::v26_2 {

// Turnover for the day excluding off-book trades.
struct TurnoverOnBookOnly {

    static constexpr const char* name = "Turnover On Book Only";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 4;
    static constexpr double denominator = 10000;
    using type = std::int64_t;

    // default constructor
    constexpr TurnoverOnBookOnly()
     : value{ 0 } {}

    // constructor for TurnoverOnBookOnly field
    constexpr explicit TurnoverOnBookOnly(const std::int64_t value)
     : value{ value } {}

    // get underlying integer of TurnoverOnBookOnly field
    [[nodiscard]] std::int64_t integer() const {
        return value;
    }

    // decimal value of TurnoverOnBookOnly field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::int64_t value;
};
}
