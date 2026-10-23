#pragma once

#include <cstddef>
#include <cstdint>

namespace cme::mdp3::v13 {

// Cumulative traded volume
struct MdEntrySizeShort {

    static constexpr const char* name = "Md Entry Size Short";
    static constexpr std::size_t size =  4;
    using type = std::int32_t;

    // default constructor
    constexpr MdEntrySizeShort()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit MdEntrySizeShort(const std::int32_t value)
     : value{ value } {}

    // get value of MdEntrySizeShort field
    [[nodiscard]] std::int32_t get() const {
        return value;
    }

  protected:
    std::int32_t value;
};
}
