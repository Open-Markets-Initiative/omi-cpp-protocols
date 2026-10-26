#pragma once

#include <cstddef>
#include <cstdint>

namespace lseg::lse::level2mbo::gtp::v26_2 {

// Count of all trades for the day.
struct NumberOfTrades {

    static constexpr const char* name = "Number Of Trades";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr NumberOfTrades()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit NumberOfTrades(const std::uint32_t value)
     : value{ value } {}

    // get value of NumberOfTrades field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
