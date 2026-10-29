#pragma once

#include <cstddef>
#include <cstdint>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1 {

// prefix
struct Prefix {

    static constexpr const char* name = "Prefix";
    static constexpr std::size_t size =  2;
    using type = std::uint16_t;

    // default constructor
    constexpr Prefix()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit Prefix(const std::uint16_t value)
     : value{ value } {}

    // get value of Prefix field
    [[nodiscard]] std::uint16_t get() const {
        return value;
    }

  protected:
    std::uint16_t value;
};
}
