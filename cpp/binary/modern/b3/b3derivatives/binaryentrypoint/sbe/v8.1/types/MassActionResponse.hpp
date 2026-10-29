#pragma once

#include <cstddef>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1 {


// massActionResponse
struct MassActionResponse {

    static constexpr auto name = "Mass Action Response";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr MassActionResponse()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit MassActionResponse(const char &value)
     : value{ value } {}

    // get value of MassActionResponse field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
