#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace nasdaq::phlxoptions::topofmarket::itch::v3_4 {


// Sub-version of this interface. Currently set to 0.
struct Subversion {

    static constexpr auto name = "Subversion";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr Subversion()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit Subversion(const std::uint8_t &value)
     : value{ value } {}

    // get value of Subversion field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
