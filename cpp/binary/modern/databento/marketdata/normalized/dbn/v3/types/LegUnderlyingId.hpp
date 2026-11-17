// Databento.MarketData.Normalized.Dbn.v3: types/LegUnderlyingId.hpp
#pragma once

#include <cstddef>
#include <cstdint>

namespace databento::marketdata::normalized::dbn::v3 {

// The leg underlying id
struct LegUnderlyingId {

    static constexpr const char* name = "Leg Underlying Id";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr LegUnderlyingId()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit LegUnderlyingId(const std::uint32_t value)
     : value{ value } {}

    // get value of LegUnderlyingId field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
