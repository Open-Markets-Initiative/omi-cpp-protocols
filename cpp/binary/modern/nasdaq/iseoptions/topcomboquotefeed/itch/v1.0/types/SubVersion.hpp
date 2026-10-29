#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace nasdaq::iseoptions::topcomboquotefeed::itch::v1_0 {


// Sub-version of this interface. Currently set to 0.
struct SubVersion {

    static constexpr auto name = "Sub Version";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr SubVersion()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit SubVersion(const std::uint8_t &value)
     : value{ value } {}

    // get value of SubVersion field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
