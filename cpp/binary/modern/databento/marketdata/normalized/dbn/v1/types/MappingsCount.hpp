// Databento.MarketData.Normalized.Dbn.v1: types/MappingsCount.hpp
#pragma once

#include <cstddef>
#include <cstdint>

namespace databento::marketdata::normalized::dbn::v1 {

// The number of symbol mappings
struct MappingsCount {

    static constexpr const char* name = "Mappings Count";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr MappingsCount()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit MappingsCount(const std::uint32_t value)
     : value{ value } {}

    // get value of MappingsCount field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
