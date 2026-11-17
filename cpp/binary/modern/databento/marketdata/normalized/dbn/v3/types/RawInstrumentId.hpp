// Databento.MarketData.Normalized.Dbn.v3: types/RawInstrumentId.hpp
#pragma once

#include <cstddef>
#include <cstdint>

namespace databento::marketdata::normalized::dbn::v3 {

// The instrument ID assigned by the publisher; may be the same as instrument_id
struct RawInstrumentId {

    static constexpr const char* name = "Raw Instrument Id";
    static constexpr std::size_t size =  8;
    using type = std::uint64_t;

    // default constructor
    constexpr RawInstrumentId()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit RawInstrumentId(const std::uint64_t value)
     : value{ value } {}

    // get value of RawInstrumentId field
    [[nodiscard]] std::uint64_t get() const {
        return value;
    }

  protected:
    std::uint64_t value;
};
}
