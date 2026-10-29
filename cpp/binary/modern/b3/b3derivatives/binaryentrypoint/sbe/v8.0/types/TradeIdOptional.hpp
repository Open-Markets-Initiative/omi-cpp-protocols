#pragma once

#include <cstddef>
#include <cstdint>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0 {

// tradeID
struct TradeIdOptional {

    static constexpr const char* name = "Trade Id Optional";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;
static const type no_value = 0;

    // default constructor
    constexpr TradeIdOptional()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit TradeIdOptional(const std::uint32_t value)
     : value{ value } {}

    // get value of TradeIdOptional field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
