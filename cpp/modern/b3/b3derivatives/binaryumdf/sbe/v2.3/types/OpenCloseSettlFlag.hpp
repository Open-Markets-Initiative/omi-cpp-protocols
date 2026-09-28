#pragma once

#include <cstddef>
#include <cstdint>

namespace b3::b3derivatives::binaryumdf::sbe::v2_3 {


// openCloseSettlFlag
struct OpenCloseSettlFlag {

    static constexpr auto name = "Open Close Settl Flag";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr OpenCloseSettlFlag()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit OpenCloseSettlFlag(const std::uint8_t &value)
     : value{ value } {}

    // get value of OpenCloseSettlFlag field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
