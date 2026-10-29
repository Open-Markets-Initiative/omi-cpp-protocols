#pragma once

#include <cstddef>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0 {


// Client system information.
struct ClientAppNameData {

    static constexpr auto name = "Client App Name Data";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr ClientAppNameData()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit ClientAppNameData(const char &value)
     : value{ value } {}

    // get value of ClientAppNameData field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
