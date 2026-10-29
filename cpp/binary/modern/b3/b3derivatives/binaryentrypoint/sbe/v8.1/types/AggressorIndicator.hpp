#pragma once

#include <cstddef>
#include <cstdint>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1 {


// aggressorIndicator
struct AggressorIndicator {

    static constexpr auto name = "Aggressor Indicator";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr AggressorIndicator()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit AggressorIndicator(const std::uint8_t &value)
     : value{ value } {}

    // get value of AggressorIndicator field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
