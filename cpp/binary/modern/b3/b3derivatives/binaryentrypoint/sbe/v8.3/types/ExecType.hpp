#pragma once

#include <cstddef>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3 {


// execType
struct ExecType {

    static constexpr auto name = "Exec Type";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr ExecType()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit ExecType(const char &value)
     : value{ value } {}

    // get value of ExecType field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
