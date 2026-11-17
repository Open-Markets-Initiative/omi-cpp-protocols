// Cme.Globex.Mdp3.Sbe.v1.13: types/TradeableSize.hpp
#pragma once

#include <cstddef>
#include <cstdint>

namespace cme::mdp3::v13 {

// Tradeable qty
struct TradeableSize {

    static constexpr const char* name = "Tradeable Size";
    static constexpr std::size_t size =  4;
    using type = std::int32_t;
static const type no_value = 2147483647;

    // default constructor: the null the model states, where it states one
    constexpr TradeableSize()
     : value{ no_value } {}

    // standard constructor
    constexpr explicit TradeableSize(const std::int32_t value)
     : value{ value } {}

    // get value of TradeableSize field
    [[nodiscard]] std::int32_t get() const {
        return value;
    }

  protected:
    std::int32_t value;
};
}
