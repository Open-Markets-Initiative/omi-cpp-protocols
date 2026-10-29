#pragma once

#include <cstddef>
#include <cstdint>

namespace bse::bseindia::eobi::fbe::v1_4 {

// Quantity.
struct DisplayQty {

    static constexpr const char* name = "Display Qty";
    static constexpr std::size_t size =  8;
    using type = std::int64_t;

    // default constructor
    constexpr DisplayQty()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit DisplayQty(const std::int64_t value)
     : value{ value } {}

    // get value of DisplayQty field
    [[nodiscard]] std::int64_t get() const {
        return value;
    }

  protected:
    std::int64_t value;
};
}
