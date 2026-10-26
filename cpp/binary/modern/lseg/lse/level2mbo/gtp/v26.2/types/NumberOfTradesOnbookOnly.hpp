#pragma once

#include <cstddef>
#include <cstdint>

namespace lseg::lse::level2mbo::gtp::v26_2 {

// Count of trades for the day excluding off-book trades.
struct NumberOfTradesOnbookOnly {

    static constexpr const char* name = "Number Of Trades Onbook Only";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr NumberOfTradesOnbookOnly()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit NumberOfTradesOnbookOnly(const std::uint32_t value)
     : value{ value } {}

    // get value of NumberOfTradesOnbookOnly field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
