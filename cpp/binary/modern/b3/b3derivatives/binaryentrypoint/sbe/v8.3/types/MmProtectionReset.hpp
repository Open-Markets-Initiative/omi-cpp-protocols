#pragma once

#include <cstddef>
#include <cstdint>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3 {


// mmProtectionReset
struct MmProtectionReset {

    static constexpr auto name = "Mm Protection Reset";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr MmProtectionReset()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit MmProtectionReset(const std::uint8_t &value)
     : value{ value } {}

    // get value of MmProtectionReset field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
