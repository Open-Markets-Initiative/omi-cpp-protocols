#pragma once

#include <cstddef>
#include <cstdint>

namespace b3::b3derivatives::binaryumdf::sbe::v2_3 {


// openCloseSettlFlag
struct OpenCloseSettlFlagOptional {

    static constexpr auto name = "Open Close Settl Flag Optional";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;
static const type no_value = 255;

    // default constructor
    constexpr OpenCloseSettlFlagOptional()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit OpenCloseSettlFlagOptional(const std::uint8_t &value)
     : value{ value } {}

    // get value of OpenCloseSettlFlagOptional field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
