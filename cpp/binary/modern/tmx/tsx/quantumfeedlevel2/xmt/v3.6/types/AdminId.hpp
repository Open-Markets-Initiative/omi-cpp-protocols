// Tmx.Tsx.QuantumFeedLevel2.Xmt.v3.6: types/AdminId.hpp
#pragma once

#include <cstddef>
#include <cstdint>

namespace tmx::tsx::quantumfeedlevel2::xmt::v3_6 {


// Admin ID for short window (1 to 255). Note: 0 is not allowed as a value.
struct AdminId {

    static constexpr auto name = "Admin Id";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr AdminId()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit AdminId(const std::uint8_t &value)
     : value{ value } {}

    // get value of AdminId field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
