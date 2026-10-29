#pragma once

#include <cstddef>
#include <cstdint>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0 {


// cancelOnDisconnectType
struct CancelOnDisconnectType {

    static constexpr auto name = "Cancel On Disconnect Type";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr CancelOnDisconnectType()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit CancelOnDisconnectType(const std::uint8_t &value)
     : value{ value } {}

    // get value of CancelOnDisconnectType field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
