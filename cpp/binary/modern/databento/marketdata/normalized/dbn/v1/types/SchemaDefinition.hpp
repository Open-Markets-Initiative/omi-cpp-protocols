// Databento.MarketData.Normalized.Dbn.v1: types/SchemaDefinition.hpp
#pragma once

#include <array>
#include <cstddef>

namespace databento::marketdata::normalized::dbn::v1 {


// The schema definition; always empty
struct SchemaDefinition {

    static constexpr auto name = "Schema Definition";
    static constexpr std::size_t size = 0;

    // underlying type
    using type = std::array<std::uint8_t, size>;

    // default constructor
    constexpr SchemaDefinition()
     : value{} {}

  protected:
    type value;
};
}
