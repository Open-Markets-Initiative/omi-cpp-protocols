#pragma once

#include <cstddef>
#include <cstdint>

namespace cme::mdp3::v8 {


// Error code for reject reason
struct ErrorCodes {

    static constexpr auto name = "Error Codes";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr ErrorCodes()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit ErrorCodes(const std::uint8_t &value)
     : value{ value } {}

    // get value of ErrorCodes field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
