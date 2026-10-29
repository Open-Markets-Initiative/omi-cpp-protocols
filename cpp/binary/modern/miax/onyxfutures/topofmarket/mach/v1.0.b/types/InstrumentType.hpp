#pragma once

#include <cstddef>

namespace miax::onyxfutures::topofmarket::mach::v1_0_b {


// ‘F’ = Futures
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
