#pragma once

#include <cstddef>
#include <cstdint>

namespace cme::mdp3::v9 {


// Book depth
struct MarketDepth {

    static constexpr auto name = "Market Depth";
    static constexpr std::size_t size = 1;
    using type = std::int8_t;

    // default constructor
    constexpr MarketDepth()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit MarketDepth(const std::int8_t &value)
     : value{ value } {}

    // get value of MarketDepth field
    [[nodiscard]] std::int8_t get() const {
        return value;
    }

  protected:
    std::int8_t value;
};
}
