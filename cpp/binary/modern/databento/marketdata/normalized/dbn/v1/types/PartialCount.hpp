// Databento.MarketData.Normalized.Dbn.v1: types/PartialCount.hpp
#pragma once

#include <cstddef>
#include <cstdint>

namespace databento::marketdata::normalized::dbn::v1 {

// The number of symbols that did not resolve for at least one day in the query time range
struct PartialCount {

    static constexpr const char* name = "Partial Count";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr PartialCount()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit PartialCount(const std::uint32_t value)
     : value{ value } {}

    // get value of PartialCount field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
