#pragma once

#include <cstddef>
#include <cstdint>

namespace bse::bseindia::eobi::fbe::v1_4 {


// Miscellaneous state information.
struct TradingSessionId {

    static constexpr auto name = "Trading Session Id";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr TradingSessionId()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit TradingSessionId(const std::uint8_t &value)
     : value{ value } {}

    // get value of TradingSessionId field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
