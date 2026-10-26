#pragma once

#include <cstddef>
#include <cstdint>

namespace cme::mdp3::v13 {

// The total open interest for the market at the close of the prior trading session.
struct OpenInterestQty {

    static constexpr const char* name = "Open Interest Qty";
    static constexpr std::size_t size =  4;
    using type = std::int32_t;
static const type no_value = 2147483647;

    // default constructor
    constexpr OpenInterestQty()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit OpenInterestQty(const std::int32_t value)
     : value{ value } {}

    // get value of OpenInterestQty field
    [[nodiscard]] std::int32_t get() const {
        return value;
    }

  protected:
    std::int32_t value;
};
}
