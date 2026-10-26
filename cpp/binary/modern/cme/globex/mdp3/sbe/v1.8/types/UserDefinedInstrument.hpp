#pragma once

#include <cstddef>

namespace cme::mdp3::v8 {


// User-defined instruments flag
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
