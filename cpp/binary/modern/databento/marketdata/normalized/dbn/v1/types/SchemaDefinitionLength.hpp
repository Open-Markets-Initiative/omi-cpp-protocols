// Databento.MarketData.Normalized.Dbn.v1: types/SchemaDefinitionLength.hpp
#pragma once

#include <cstddef>
#include <cstdint>

namespace databento::marketdata::normalized::dbn::v1 {

// The length of the schema definition; always 0
struct SchemaDefinitionLength {

    static constexpr const char* name = "Schema Definition Length";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr SchemaDefinitionLength()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit SchemaDefinitionLength(const std::uint32_t value)
     : value{ value } {}

    // get value of SchemaDefinitionLength field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
