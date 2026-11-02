#pragma once

#include <cstddef>
#include <cstdint>

namespace databento::marketdata::normalized::dbn::v3 {

// The type of statistic value contained in the message
struct StatType {

    static constexpr const char* name = "Stat Type";
    static constexpr std::size_t size =  2;
    using type = std::uint16_t;

    // default constructor
    constexpr StatType()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit StatType(const std::uint16_t value)
     : value{ value } {}

    // get value of StatType field
    [[nodiscard]] std::uint16_t get() const {
        return value;
    }

  protected:
    std::uint16_t value;
};
}
