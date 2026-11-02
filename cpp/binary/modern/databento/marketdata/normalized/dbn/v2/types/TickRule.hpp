#pragma once

#include <cstddef>
#include <cstdint>

namespace databento::marketdata::normalized::dbn::v2 {


// The tick rule
struct TickRule {

    static constexpr auto name = "Tick Rule";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr TickRule()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit TickRule(const std::uint8_t &value)
     : value{ value } {}

    // get value of TickRule field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
