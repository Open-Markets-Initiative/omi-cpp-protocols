// Databento.MarketData.Normalized.Dbn.v3: types/MetadataPadding.hpp
#pragma once

#include <array>
#include <cstddef>

namespace databento::marketdata::normalized::dbn::v3 {


// Padding to an 8 byte boundary
struct MetadataPadding {

    static constexpr auto name = "Metadata Padding";
    static constexpr std::size_t size = 0;

    // underlying type
    using type = std::array<std::uint8_t, size>;

    // default constructor
    constexpr MetadataPadding()
     : value{} {}

  protected:
    type value;
};
}
