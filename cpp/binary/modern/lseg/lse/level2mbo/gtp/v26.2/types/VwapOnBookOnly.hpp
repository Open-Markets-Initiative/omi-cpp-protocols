#pragma once

#include <cstddef>
#include <cstdint>

namespace lseg::lse::level2mbo::gtp::v26_2 {

// Volume weighted average price for the day excluding off-book trades.
struct VwapOnBookOnly {

    static constexpr const char* name = "Vwap On Book Only";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 4;
    static constexpr double denominator = 10000;
    using type = std::int64_t;

    // default constructor
    constexpr VwapOnBookOnly()
     : value{ 0 } {}

    // constructor for VwapOnBookOnly field
    constexpr explicit VwapOnBookOnly(const std::int64_t value)
     : value{ value } {}

    // get underlying integer of VwapOnBookOnly field
    [[nodiscard]] std::int64_t integer() const {
        return value;
    }

    // decimal value of VwapOnBookOnly field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::int64_t value;
};
}
