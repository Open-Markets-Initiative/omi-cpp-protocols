// Databento.MarketData.Normalized.Dbn.v3: types/Activation.hpp
#pragma once

#include <cstddef>
#include <cstdint>

namespace databento::marketdata::normalized::dbn::v3 {


// The time of instrument activation expressed as the number of nanoseconds since the UNIX epoch
struct Activation {

    static constexpr auto name = "Activation";
    static constexpr std::size_t size = 8;

    // underlying type
    using type = std::uint64_t;
static const type no_value = 18446744073709551615ULL;

    // default constructor
    constexpr Activation()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit Activation(const std::uint64_t &value)
     : value{ value } {}

    // get value of Activation field
    [[nodiscard]] std::uint64_t get() const {
        return value;
    }

  protected:
    std::uint64_t value;
};
}
