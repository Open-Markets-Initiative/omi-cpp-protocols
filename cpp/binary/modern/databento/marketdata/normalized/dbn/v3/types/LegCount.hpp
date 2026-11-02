#pragma once

#include <cstddef>
#include <cstdint>

namespace databento::marketdata::normalized::dbn::v3 {

// The leg count
struct LegCount {

    static constexpr const char* name = "Leg Count";
    static constexpr std::size_t size =  2;
    using type = std::uint16_t;

    // default constructor
    constexpr LegCount()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit LegCount(const std::uint16_t value)
     : value{ value } {}

    // get value of LegCount field
    [[nodiscard]] std::uint16_t get() const {
        return value;
    }

  protected:
    std::uint16_t value;
};
}
