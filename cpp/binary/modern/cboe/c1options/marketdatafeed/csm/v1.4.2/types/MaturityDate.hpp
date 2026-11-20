// Cboe.C1Options.MarketDataFeed.Csm.v1.4.2: types/MaturityDate.hpp
#pragma once

#include <bit>
#include <chrono>
#include <cstddef>
#include <cstdint>

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

// Expiration date: Format is “YYYYMMDD”. This field is required for options and futures
struct MaturityDate {

    static constexpr const char* name = "Maturity Date";
    static constexpr std::size_t size =  8;
    using type = std::uint64_t;

    // default constructor
    constexpr MaturityDate()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit MaturityDate(const std::uint64_t value)
     : value{ std::byteswap(value) } {}

    // get value of MaturityDate field
    [[nodiscard]] std::uint64_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint64_t value;
};
}
