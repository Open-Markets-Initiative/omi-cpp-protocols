// Databento.MarketData.Normalized.Dbn.v3: types/RecordLength.hpp
#pragma once

#include <cstddef>
#include <cstdint>

namespace databento::marketdata::normalized::dbn::v3 {


// The length of the record in 32-bit words, including this header and any ts_out trailer
struct RecordLength {

    static constexpr auto name = "Record Length";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr RecordLength()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit RecordLength(const std::uint8_t &value)
     : value{ value } {}

    // get value of RecordLength field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
