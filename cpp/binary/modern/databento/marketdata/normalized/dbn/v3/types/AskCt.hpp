// Databento.MarketData.Normalized.Dbn.v3: types/AskCt.hpp
#pragma once

#include <cstddef>
#include <cstdint>

namespace databento::marketdata::normalized::dbn::v3 {

// The number of ask orders
struct AskCt {

    static constexpr const char* name = "Ask Ct";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr AskCt()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit AskCt(const std::uint32_t value)
     : value{ value } {}

    // get value of AskCt field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
