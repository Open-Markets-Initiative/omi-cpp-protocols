#pragma once

#include <array>
#include <cstddef>

namespace databento::marketdata::normalized::dbn::v1 {


// Reserved, 47 bytes
struct MetadataReserved {

    static constexpr auto name = "Metadata Reserved";
    static constexpr std::size_t size = 47;

    // underlying type
    using type = std::array<std::uint8_t, size>;

    // default constructor
    constexpr MetadataReserved()
     : value{} {}

  protected:
    type value;
};
}
