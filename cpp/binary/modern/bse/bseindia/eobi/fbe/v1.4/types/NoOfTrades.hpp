#pragma once

#include <cstddef>
#include <cstdint>

namespace bse::bseindia::eobi::fbe::v1_4 {

// Total number of trades.
struct NoOfTrades {

    static constexpr const char* name = "No Of Trades";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr NoOfTrades()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit NoOfTrades(const std::uint32_t value)
     : value{ value } {}

    // get value of NoOfTrades field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
