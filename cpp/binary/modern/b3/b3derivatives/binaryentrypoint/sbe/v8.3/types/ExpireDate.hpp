#pragma once

#include <cstddef>
#include <cstdint>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3 {

// expireDate
struct ExpireDate {

    static constexpr const char* name = "Expire Date";
    static constexpr std::size_t size =  2;
    using type = std::uint16_t;
static const type no_value = 0;

    // default constructor
    constexpr ExpireDate()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit ExpireDate(const std::uint16_t value)
     : value{ value } {}

    // get value of ExpireDate field
    [[nodiscard]] std::uint16_t get() const {
        return value;
    }

  protected:
    std::uint16_t value;
};
}
