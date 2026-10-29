#pragma once

#include <cstddef>
#include <cstdint>

namespace bse::bseindia::eobi::fbe::v1_4 {


// Set in the first packet header after a market data fail over or restart, 0 No Reset and 1 Reset
struct ApplSeqResetIndicator {

    static constexpr auto name = "Appl Seq Reset Indicator";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr ApplSeqResetIndicator()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit ApplSeqResetIndicator(const std::uint8_t &value)
     : value{ value } {}

    // get value of ApplSeqResetIndicator field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
