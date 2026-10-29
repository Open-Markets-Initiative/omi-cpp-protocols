#pragma once

#include <cstddef>

namespace miax::onyxfutures::topofmarket::mach::v1_0_b {


// Indicates whether the Instrument ID has been assigned by the exchange or from an external industry source
struct InstrumentIdSource {

    static constexpr auto name = "Instrument Id Source";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr InstrumentIdSource()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit InstrumentIdSource(const char &value)
     : value{ value } {}

    // get value of InstrumentIdSource field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
