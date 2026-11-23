// Tmx.Tsx.QuantumFeedLevel2.Xmt.v3.6: types/TradeDate.hpp
#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>

namespace tmx::tsx::quantumfeedlevel2::xmt::v3_6 {

// Effective Date Of The Trade Will Only Be Filled When The Effective Date Is Different From The Current Date
struct TradeDate {

    static constexpr const char* name = "Trade Date";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;
static const type no_value = 0;

    // default constructor: the null the model states, where it states one
    constexpr TradeDate()
     : value{ no_value } {}

    // standard constructor
    constexpr explicit TradeDate(const std::uint32_t value)
     : value{ value } {}

    // get value of TradeDate field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
