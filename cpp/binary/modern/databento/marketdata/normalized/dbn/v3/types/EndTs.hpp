// Databento.MarketData.Normalized.Dbn.v3: types/EndTs.hpp
#pragma once

#include <cstddef>
#include <cstdint>

namespace databento::marketdata::normalized::dbn::v3 {


// The end of the mapping interval expressed as the number of nanoseconds since the UNIX epoch
struct EndTs {

    static constexpr auto name = "End Ts";
    static constexpr std::size_t size = 8;

    // underlying type
    using type = std::uint64_t;
static const type no_value = 18446744073709551615ULL;

    // default constructor
    constexpr EndTs()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit EndTs(const std::uint64_t &value)
     : value{ value } {}

    // get value of EndTs field
    [[nodiscard]] std::uint64_t get() const {
        return value;
    }

  protected:
    std::uint64_t value;
};
}
