#pragma once

#include <cstddef>
#include <cstdint>

namespace databento::marketdata::normalized::dbn::v3 {

// The length of the metadata after this field, in bytes
struct MetadataLength {

    static constexpr const char* name = "Metadata Length";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr MetadataLength()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit MetadataLength(const std::uint32_t value)
     : value{ value } {}

    // get value of MetadataLength field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
