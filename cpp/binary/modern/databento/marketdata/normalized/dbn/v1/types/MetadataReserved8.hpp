// Databento.MarketData.Normalized.Dbn.v1: types/MetadataReserved8.hpp
#pragma once

#include <array>
#include <cstddef>

namespace databento::marketdata::normalized::dbn::v1 {


// Reserved, 8 bytes; the deprecated record count
struct MetadataReserved8 {

    static constexpr auto name = "Metadata Reserved 8";
    static constexpr std::size_t size = 8;

    // underlying type
    using type = std::array<std::uint8_t, size>;

    // default constructor
    constexpr MetadataReserved8()
     : value{} {}

  protected:
    type value;
};
}
