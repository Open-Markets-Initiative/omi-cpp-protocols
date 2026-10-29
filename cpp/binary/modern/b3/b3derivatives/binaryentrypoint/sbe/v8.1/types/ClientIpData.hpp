#pragma once

#include <cstddef>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1 {


// Client system information.
struct ClientIpData {

    static constexpr auto name = "Client Ip Data";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr ClientIpData()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit ClientIpData(const char &value)
     : value{ value } {}

    // get value of ClientIpData field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
