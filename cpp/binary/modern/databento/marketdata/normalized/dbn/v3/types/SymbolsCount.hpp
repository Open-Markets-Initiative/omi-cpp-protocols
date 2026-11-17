// Databento.MarketData.Normalized.Dbn.v3: types/SymbolsCount.hpp
#pragma once

#include <cstddef>
#include <cstdint>

namespace databento::marketdata::normalized::dbn::v3 {

// The number of query input symbols
struct SymbolsCount {

    static constexpr const char* name = "Symbols Count";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr SymbolsCount()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit SymbolsCount(const std::uint32_t value)
     : value{ value } {}

    // get value of SymbolsCount field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
