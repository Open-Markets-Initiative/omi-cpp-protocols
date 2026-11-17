// Databento.MarketData.Normalized.Dbn.v2: types/NotFoundCount.hpp
#pragma once

#include <cstddef>
#include <cstdint>

namespace databento::marketdata::normalized::dbn::v2 {

// The number of symbols that did not resolve for any day in the query time range
struct NotFoundCount {

    static constexpr const char* name = "Not Found Count";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr NotFoundCount()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit NotFoundCount(const std::uint32_t value)
     : value{ value } {}

    // get value of NotFoundCount field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
