#pragma once

#include <cstddef>
#include <cstdint>

namespace cme::mdp3::v8 {

// Unique Trade ID per instrument and Trading Date
struct TradeId {

    static constexpr const char* name = "Trade Id";
    static constexpr std::size_t size =  4;
    using type = std::int32_t;

    // default constructor
    constexpr TradeId()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit TradeId(const std::int32_t value)
     : value{ value } {}

    // get value of TradeId field
    [[nodiscard]] std::int32_t get() const {
        return value;
    }

  protected:
    std::int32_t value;
};
}
