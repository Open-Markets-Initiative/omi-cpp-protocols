#pragma once

#include <cstddef>
#include <cstdint>

namespace b3::b3derivatives::binaryumdf::sbe::v1_7 {

// Length of a string, in bytes. For instance, the string 'Ação', converted to UTF-8, has 6 bytes, so length = 6.
struct UrlLinkLength {

    static constexpr const char* name = "Url Link Length";
    static constexpr std::size_t size =  2;
    using type = std::uint16_t;

    // default constructor
    constexpr UrlLinkLength()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit UrlLinkLength(const std::uint16_t value)
     : value{ value } {}

    // get value of UrlLinkLength field
    [[nodiscard]] std::uint16_t get() const {
        return value;
    }

  protected:
    std::uint16_t value;
};
}
