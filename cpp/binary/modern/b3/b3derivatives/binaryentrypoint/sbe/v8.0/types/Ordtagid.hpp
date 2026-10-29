#pragma once

#include <cstddef>
#include <cstdint>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0 {


// ordTagID
struct Ordtagid {

    static constexpr auto name = "OrdTagId";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;
static const type no_value = 0;

    // default constructor
    constexpr Ordtagid()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit Ordtagid(const std::uint8_t &value)
     : value{ value } {}

    // get value of Ordtagid field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
