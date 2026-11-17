// Cboe.C1Options.MarketDataFeed.Csm.v1.4.2: types/EopMantissa.hpp
#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

// The expected opening price
struct EopMantissa {

    static constexpr const char* name = "Eop Mantissa";
    static constexpr std::size_t size =  4;
    using type = std::int32_t;

    // default constructor
    constexpr EopMantissa()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit EopMantissa(const std::int32_t value)
     : value{ std::byteswap(value) } {}

    // get value of EopMantissa field
    [[nodiscard]] std::int32_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::int32_t value;
};
}
