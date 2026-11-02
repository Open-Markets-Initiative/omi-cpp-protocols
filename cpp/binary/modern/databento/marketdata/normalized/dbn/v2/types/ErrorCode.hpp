#pragma once

#include <cstddef>
#include <cstdint>

namespace databento::marketdata::normalized::dbn::v2 {


// The error code
struct ErrorCode {

    static constexpr auto name = "Error Code";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr ErrorCode()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit ErrorCode(const std::uint8_t &value)
     : value{ value } {}

    // get value of ErrorCode field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
