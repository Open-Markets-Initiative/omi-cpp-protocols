// Cme.Globex.Mdp3.Sbe.v1.13: types/MdEntrySizeOptional.hpp
#pragma once

#include <cstddef>
#include <cstdint>

namespace cme::mdp3::v13 {

// Aggregate booked qty at price level, notional
struct MdEntrySizeOptional {

    static constexpr const char* name = "Md Entry Size Optional";
    static constexpr std::size_t size =  8;
    using type = std::uint64_t;
static const type no_value = 18446744073709551615ULL;

    // default constructor: the null the model states, where it states one
    constexpr MdEntrySizeOptional()
     : value{ no_value } {}

    // standard constructor
    constexpr explicit MdEntrySizeOptional(const std::uint64_t value)
     : value{ value } {}

    // get value of MdEntrySizeOptional field
    [[nodiscard]] std::uint64_t get() const {
        return value;
    }

  protected:
    std::uint64_t value;
};
}
