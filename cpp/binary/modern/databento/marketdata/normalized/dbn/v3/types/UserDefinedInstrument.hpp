// Databento.MarketData.Normalized.Dbn.v3: types/UserDefinedInstrument.hpp
#pragma once

#include <cstddef>

namespace databento::marketdata::normalized::dbn::v3 {


// Indicates if the instrument is user defined
struct UserDefinedInstrument {

    static constexpr auto name = "User Defined Instrument";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr UserDefinedInstrument()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit UserDefinedInstrument(const char &value)
     : value{ value } {}

    // get value of UserDefinedInstrument field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
