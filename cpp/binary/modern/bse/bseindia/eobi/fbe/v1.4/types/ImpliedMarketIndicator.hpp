#pragma once

#include <cstddef>
#include <cstdint>

namespace bse::bseindia::eobi::fbe::v1_4 {


// Indicates that an implied market to be created for either the legs of a multi-leg instrument or for the multi-leg instrument based on the existence of the legs.
struct ImpliedMarketIndicator {

    static constexpr auto name = "Implied Market Indicator";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr ImpliedMarketIndicator()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit ImpliedMarketIndicator(const std::uint8_t &value)
     : value{ value } {}

    // get value of ImpliedMarketIndicator field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
