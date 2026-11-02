#pragma once

#include <cstddef>
#include <cstdint>

namespace cme::mdp3::v5 {

// Market Data entry size
struct MdEntrySizeOptional {

    static constexpr const char* name = "Md Entry Size Optional";
    static constexpr std::size_t size =  4;
    using type = std::int32_t;
static const type no_value = 2147483647;

    // default constructor: the null the model states, where it states one
    constexpr MdEntrySizeOptional()
     : value{ no_value } {}

    // standard constructor
    constexpr explicit MdEntrySizeOptional(const std::int32_t value)
     : value{ value } {}

    // get value of MdEntrySizeOptional field
    [[nodiscard]] std::int32_t get() const {
        return value;
    }

  protected:
    std::int32_t value;
};
}
