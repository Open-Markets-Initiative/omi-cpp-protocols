#pragma once

#include <cstddef>
#include <cstdint>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3 {

// noRelatedTrades
struct NoRelatedTrades {

    static constexpr const char* name = "No Related Trades";
    static constexpr std::size_t size =  2;
    using type = std::uint16_t;

    // default constructor
    constexpr NoRelatedTrades()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit NoRelatedTrades(const std::uint16_t value)
     : value{ value } {}

    // get value of NoRelatedTrades field
    [[nodiscard]] std::uint16_t get() const {
        return value;
    }

  protected:
    std::uint16_t value;
};
}
