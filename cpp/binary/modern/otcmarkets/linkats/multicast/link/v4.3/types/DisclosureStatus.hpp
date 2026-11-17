// OtcMarkets.LinkAts.Multicast.Link.v4.3: types/DisclosureStatus.hpp
#pragma once

#include <cstddef>
#include <cstdint>

namespace otcmarkets::linkats::multicast::link::v4_3 {


// Current disclosure status of the issuer.
struct DisclosureStatus {

    static constexpr auto name = "Disclosure Status";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr DisclosureStatus()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit DisclosureStatus(const std::uint8_t &value)
     : value{ value } {}

    // get value of DisclosureStatus field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
