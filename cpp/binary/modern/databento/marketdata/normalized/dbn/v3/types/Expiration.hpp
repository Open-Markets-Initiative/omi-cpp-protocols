// Databento.MarketData.Normalized.Dbn.v3: types/Expiration.hpp
#pragma once

#include <cstddef>
#include <cstdint>

namespace databento::marketdata::normalized::dbn::v3 {


// The last eligible trade time expressed as the number of nanoseconds since the UNIX epoch
struct Expiration {

    static constexpr auto name = "Expiration";
    static constexpr std::size_t size = 8;

    // underlying type
    using type = std::uint64_t;
static const type no_value = 18446744073709551615ULL;

    // default constructor
    constexpr Expiration()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit Expiration(const std::uint64_t &value)
     : value{ value } {}

    // get value of Expiration field
    [[nodiscard]] std::uint64_t get() const {
        return value;
    }

  protected:
    std::uint64_t value;
};
}
