#pragma once

#include <cstddef>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3 {


// settlType
struct SettlType {

    static constexpr auto name = "Settl Type";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr SettlType()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit SettlType(const char &value)
     : value{ value } {}

    // get value of SettlType field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
