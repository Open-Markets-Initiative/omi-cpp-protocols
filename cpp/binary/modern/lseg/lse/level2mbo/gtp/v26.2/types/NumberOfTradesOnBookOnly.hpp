#pragma once

#include <cstddef>
#include <cstdint>

namespace lseg::lse::level2mbo::gtp::v26_2 {

// Count of trades for the day excluding off-book trades.
struct NumberOfTradesOnBookOnly {

    static constexpr const char* name = "Number Of Trades On Book Only";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr NumberOfTradesOnBookOnly()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit NumberOfTradesOnBookOnly(const std::uint32_t value)
     : value{ value } {}

    // get value of NumberOfTradesOnBookOnly field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
