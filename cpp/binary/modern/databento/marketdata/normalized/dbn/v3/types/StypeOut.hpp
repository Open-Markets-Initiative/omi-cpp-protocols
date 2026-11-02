#pragma once

#include <cstddef>
#include <cstdint>

namespace databento::marketdata::normalized::dbn::v3 {


// The output symbology type
struct StypeOut {

    static constexpr auto name = "Stype Out";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr StypeOut()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit StypeOut(const std::uint8_t &value)
     : value{ value } {}

    // get value of StypeOut field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
