#pragma once

#include <cstddef>
#include <cstdint>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3 {


// mmProtectionReset
struct MmProtectionResetOptional {

    static constexpr auto name = "Mm Protection Reset Optional";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;
static const type no_value = 255;

    // default constructor
    constexpr MmProtectionResetOptional()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit MmProtectionResetOptional(const std::uint8_t &value)
     : value{ value } {}

    // get value of MmProtectionResetOptional field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
