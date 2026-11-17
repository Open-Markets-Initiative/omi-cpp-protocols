// B3.B3Derivatives.BinaryEntryPoint.Sbe.v8.3: types/Prefix.hpp
#pragma once

#include <cstddef>
#include <cstdint>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3 {

// prefix
struct Prefix {

    static constexpr const char* name = "Prefix";
    static constexpr std::size_t size =  2;
    using type = std::uint16_t;
static const type no_value = 0;

    // default constructor: the null the model states, where it states one
    constexpr Prefix()
     : value{ no_value } {}

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
