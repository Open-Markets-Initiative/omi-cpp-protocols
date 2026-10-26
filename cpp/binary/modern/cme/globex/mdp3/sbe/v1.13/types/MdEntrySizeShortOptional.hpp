#pragma once

#include <cstddef>
#include <cstdint>

namespace cme::mdp3::v13 {

// Market Data entry size
struct MdEntrySizeShortOptional {

    static constexpr const char* name = "Md Entry Size Short Optional";
    static constexpr std::size_t size =  4;
    using type = std::int32_t;
static const type no_value = 2147483647;

    // default constructor
    constexpr MdEntrySizeShortOptional()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit MdEntrySizeShortOptional(const std::int32_t value)
     : value{ value } {}

    // get value of MdEntrySizeShortOptional field
    [[nodiscard]] std::int32_t get() const {
        return value;
    }

  protected:
    std::int32_t value;
};
}
