#pragma once

#include <cstddef>
#include <cstdint>

namespace cme::mdp3::v13 {

// Trade Session Date
struct TradeDate {

    static constexpr const char* name = "Trade Date";
    static constexpr std::size_t size =  2;
    using type = std::uint16_t;
static const type no_value = 65535;

    // default constructor
    constexpr TradeDate()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit TradeDate(const std::uint16_t value)
     : value{ value } {}

    // get value of TradeDate field
    [[nodiscard]] std::uint16_t get() const {
        return value;
    }

  protected:
    std::uint16_t value;
};
}
