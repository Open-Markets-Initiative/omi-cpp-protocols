#pragma once

#include <cstddef>
#include <cstdint>

namespace b3::b3derivatives::binaryumdf::sbe::v2_2 {


// optPayoutType
struct OptPayoutType {

    static constexpr auto name = "Opt Payout Type";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;
static const type no_value = 0;

    // default constructor
    constexpr OptPayoutType()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit OptPayoutType(const std::uint8_t &value)
     : value{ value } {}

    // get value of OptPayoutType field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
