// Databento.MarketData.Normalized.Dbn.v3: types/TsOut.hpp
#pragma once

#include <cstddef>
#include <cstdint>

namespace databento::marketdata::normalized::dbn::v3 {


// Whether every record carries a ts_out trailer, the live gateway send timestamp
struct TsOut {

    static constexpr auto name = "Ts Out";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr TsOut()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit TsOut(const std::uint8_t &value)
     : value{ value } {}

    // get value of TsOut field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
