#pragma once

#include <cstddef>

namespace siac::cts::output::cta::v2_11_b {


// Identifies the instrument type relevant to the trade
struct InstrumentType {

    static constexpr auto name = "Instrument Type";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr InstrumentType()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit InstrumentType(const char &value)
     : value{ value } {}

    // get value of InstrumentType field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
