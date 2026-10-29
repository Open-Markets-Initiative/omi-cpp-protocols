#pragma once

#include <cstddef>
#include <cstdint>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3 {


// Length of client system information.
struct ClientAppVersionLength {

    static constexpr auto name = "Client App Version Length";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr ClientAppVersionLength()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit ClientAppVersionLength(const std::uint8_t &value)
     : value{ value } {}

    // get value of ClientAppVersionLength field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
