#pragma once

#include <cstddef>
#include <cstdint>

namespace b3::b3derivatives::binaryumdf::sbe::v2_2 {

// mDEntrySeller
struct MdEntrySeller {

    static constexpr const char* name = "Md Entry Seller";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;
static const type no_value = 0;

    // default constructor
    constexpr MdEntrySeller()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit MdEntrySeller(const std::uint32_t value)
     : value{ value } {}

    // get value of MdEntrySeller field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
