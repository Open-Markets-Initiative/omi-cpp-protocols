#pragma once

#include <cstddef>
#include <cstdint>

namespace databento::marketdata::normalized::dbn::v3 {

// The leg instrument id
struct LegInstrumentId {

    static constexpr const char* name = "Leg Instrument Id";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr LegInstrumentId()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit LegInstrumentId(const std::uint32_t value)
     : value{ value } {}

    // get value of LegInstrumentId field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
