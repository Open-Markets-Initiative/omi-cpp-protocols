#pragma once

#include <cstddef>
#include <cstdint>

namespace databento::marketdata::normalized::dbn::v2 {


// The type indicators for the settlement price, as a bitmap
struct SettlPriceType {

    static constexpr auto name = "Settl Price Type";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr SettlPriceType()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit SettlPriceType(const std::uint8_t &value)
     : value{ value } {}

    // get value of SettlPriceType field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
