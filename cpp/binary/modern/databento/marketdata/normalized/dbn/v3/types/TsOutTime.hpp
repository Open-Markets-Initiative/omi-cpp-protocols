// Databento.MarketData.Normalized.Dbn.v3: types/TsOutTime.hpp
#pragma once

#include <cstddef>
#include <cstdint>

namespace databento::marketdata::normalized::dbn::v3 {


// The live gateway send timestamp, present on every record when the metadata ts_out flag is set
struct TsOutTime {

    static constexpr auto name = "Ts Out Time";
    static constexpr std::size_t size = 8;

    // underlying type
    using type = std::uint64_t;

    // default constructor
    constexpr TsOutTime()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit TsOutTime(const std::uint64_t &value)
     : value{ value } {}

    // get value of TsOutTime field
    [[nodiscard]] std::uint64_t get() const {
        return value;
    }

  protected:
    std::uint64_t value;
};
}
