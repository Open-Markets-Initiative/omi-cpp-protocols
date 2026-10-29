#pragma once

#include <cstddef>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3 {


// Client system information.
struct ClientAppVersionData {

    static constexpr auto name = "Client App Version Data";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr ClientAppVersionData()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit ClientAppVersionData(const char &value)
     : value{ value } {}

    // get value of ClientAppVersionData field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
