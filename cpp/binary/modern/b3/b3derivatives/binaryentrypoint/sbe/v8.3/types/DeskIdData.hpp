#pragma once

#include <cstddef>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3 {


// Trading desk identification in ASCII format.
struct DeskIdData {

    static constexpr auto name = "Desk Id Data";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr DeskIdData()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit DeskIdData(const char &value)
     : value{ value } {}

    // get value of DeskIdData field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
