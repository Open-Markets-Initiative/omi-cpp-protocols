#pragma once

#include <cstddef>
#include <cstdint>

namespace cme::mdp3::v9 {

// Strike Price for an option instrument
struct StrikePriceEx {

    static constexpr const char* name = "Strike Price Ex";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 9;
    static constexpr double denominator = 1000000000;
    using type = std::int64_t;
static const type no_value = 9223372036854775807;

    // default constructor
    constexpr StrikePriceEx()
     : value{ 0 } {}

    // constructor for StrikePriceEx field
    constexpr explicit StrikePriceEx(const std::int64_t value)
     : value{ value } {}

    // get underlying integer of StrikePriceEx field
    [[nodiscard]] std::int64_t integer() const {
        return value;
    }

    // decimal value of StrikePriceEx field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::int64_t value;
};
}
