// Databento.MarketData.Normalized.Dbn.v3: types/LegInstrumentClass.hpp
#pragma once

#include <cstddef>

namespace databento::marketdata::normalized::dbn::v3 {


// The classification of the leg instrument
struct LegInstrumentClass {

    static constexpr auto name = "Leg Instrument Class";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr LegInstrumentClass()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit LegInstrumentClass(const char &value)
     : value{ value } {}

    // get value of LegInstrumentClass field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
