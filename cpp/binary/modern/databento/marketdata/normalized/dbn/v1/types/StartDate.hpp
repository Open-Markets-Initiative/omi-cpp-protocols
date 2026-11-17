// Databento.MarketData.Normalized.Dbn.v1: types/StartDate.hpp
#pragma once

#include <cstddef>
#include <cstdint>

namespace databento::marketdata::normalized::dbn::v1 {

// The UTC start date of the mapping interval, as a YYYYMMDD integer
struct StartDate {

    static constexpr const char* name = "Start Date";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr StartDate()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit StartDate(const std::uint32_t value)
     : value{ value } {}

    // get value of StartDate field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
