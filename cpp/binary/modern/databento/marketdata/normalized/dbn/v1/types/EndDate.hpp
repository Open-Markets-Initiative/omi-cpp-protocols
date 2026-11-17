// Databento.MarketData.Normalized.Dbn.v1: types/EndDate.hpp
#pragma once

#include <cstddef>
#include <cstdint>

namespace databento::marketdata::normalized::dbn::v1 {

// The UTC end date of the mapping interval, as a YYYYMMDD integer
struct EndDate {

    static constexpr const char* name = "End Date";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr EndDate()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit EndDate(const std::uint32_t value)
     : value{ value } {}

    // get value of EndDate field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
