// Databento.MarketData.Normalized.Dbn.v1: types/InstrumentClass.hpp
#pragma once

#include <cstddef>

namespace databento::marketdata::normalized::dbn::v1 {


// The classification of the instrument
struct InstrumentClass {

    static constexpr auto name = "Instrument Class";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr InstrumentClass()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit InstrumentClass(const char &value)
     : value{ value } {}

    // get value of InstrumentClass field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
