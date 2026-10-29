#pragma once

#include <cstddef>
#include <cstdint>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0 {


// Length of client system information.
struct ClientAppNameLength {

    static constexpr auto name = "Client App Name Length";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr ClientAppNameLength()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit ClientAppNameLength(const std::uint8_t &value)
     : value{ value } {}

    // get value of ClientAppNameLength field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
