#pragma once

#include <cstddef>
#include <cstdint>

namespace bse::bseindia::eobi::fbe::v1_4 {

// Quantity.
struct MdEntrySize {

    static constexpr const char* name = "Md Entry Size";
    static constexpr std::size_t size =  8;
    using type = std::int64_t;
static const type no_value = 0x8000000000000000;

    // default constructor: the null the model states, where it states one
    constexpr MdEntrySize()
     : value{ no_value } {}

    // standard constructor
    constexpr explicit MdEntrySize(const std::int64_t value)
     : value{ value } {}

    // get value of MdEntrySize field
    [[nodiscard]] std::int64_t get() const {
        return value;
    }

  protected:
    std::int64_t value;
};
}
