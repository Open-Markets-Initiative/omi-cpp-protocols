#pragma once

#include <cstddef>
#include <cstdint>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3 {

// daysToSettlement
struct DaysToSettlementOptional {

    static constexpr const char* name = "Days To Settlement Optional";
    static constexpr std::size_t size =  2;
    using type = std::uint16_t;
static const type no_value = 65535;

    // default constructor
    constexpr DaysToSettlementOptional()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit DaysToSettlementOptional(const std::uint16_t value)
     : value{ value } {}

    // get value of DaysToSettlementOptional field
    [[nodiscard]] std::uint16_t get() const {
        return value;
    }

  protected:
    std::uint16_t value;
};
}
