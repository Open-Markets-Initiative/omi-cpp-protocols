// Databento.MarketData.Normalized.Dbn.v3: types/MetadataReserved.hpp
#pragma once

#include <array>
#include <cstddef>

namespace databento::marketdata::normalized::dbn::v3 {


// Reserved, 53 bytes
struct MetadataReserved {

    static constexpr auto name = "Metadata Reserved";
    static constexpr std::size_t size = 53;

    // underlying type
    using type = std::array<std::uint8_t, size>;

    // default constructor
    constexpr MetadataReserved()
     : value{} {}

  protected:
    type value;
};
}
