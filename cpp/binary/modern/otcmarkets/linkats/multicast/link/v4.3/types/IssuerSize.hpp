// OtcMarkets.LinkAts.Multicast.Link.v4.3: types/IssuerSize.hpp
#pragma once

#include <cstddef>
#include <cstdint>

namespace otcmarkets::linkats::multicast::link::v4_3 {


// Size of the IssuerName field. If zero, IssuerName is not present.
struct IssuerSize {

    static constexpr auto name = "Issuer Size";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr IssuerSize()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit IssuerSize(const std::uint8_t &value)
     : value{ value } {}

    // get value of IssuerSize field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
