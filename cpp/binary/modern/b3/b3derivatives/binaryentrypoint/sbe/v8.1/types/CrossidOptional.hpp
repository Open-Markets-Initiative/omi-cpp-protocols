#pragma once

#include <cstddef>
#include <cstdint>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1 {

// crossID
struct CrossidOptional {

    static constexpr const char* name = "CrossId Optional";
    static constexpr std::size_t size =  8;
    using type = std::uint64_t;
static const type no_value = 0;

    // default constructor
    constexpr CrossidOptional()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit CrossidOptional(const std::uint64_t value)
     : value{ value } {}

    // get value of CrossidOptional field
    [[nodiscard]] std::uint64_t get() const {
        return value;
    }

  protected:
    std::uint64_t value;
};
}
