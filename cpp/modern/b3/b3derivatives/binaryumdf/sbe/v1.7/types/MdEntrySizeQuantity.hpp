#pragma once

#include <cstddef>
#include <cstdint>

namespace b3::b3derivatives::binaryumdf::sbe::v1_7 {

// mDEntrySize
struct MdEntrySizeQuantity {

    static constexpr const char* name = "Md Entry Size Quantity";
    static constexpr std::size_t size =  8;
    using type = std::int64_t;

    // default constructor
    constexpr MdEntrySizeQuantity()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit MdEntrySizeQuantity(const std::int64_t value)
     : value{ value } {}

    // get value of MdEntrySizeQuantity field
    [[nodiscard]] std::int64_t get() const {
        return value;
    }

  protected:
    std::int64_t value;
};
}
