#pragma once

#include <cstddef>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0 {


// settlType
struct SettlTypeOptional {

    static constexpr auto name = "Settl Type Optional";
    static constexpr std::size_t size = 1;
    using type = char;
static const type no_value = '0';

    // default constructor
    constexpr SettlTypeOptional()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit SettlTypeOptional(const char &value)
     : value{ value } {}

    // get value of SettlTypeOptional field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
