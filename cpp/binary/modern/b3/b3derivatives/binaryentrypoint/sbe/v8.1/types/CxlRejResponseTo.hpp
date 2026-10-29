#pragma once

#include <cstddef>
#include <cstdint>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1 {


// cxlRejResponseTo
struct CxlRejResponseTo {

    static constexpr auto name = "Cxl Rej Response To";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr CxlRejResponseTo()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit CxlRejResponseTo(const std::uint8_t &value)
     : value{ value } {}

    // get value of CxlRejResponseTo field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
