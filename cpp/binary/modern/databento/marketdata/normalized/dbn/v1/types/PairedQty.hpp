#pragma once

#include <cstddef>
#include <cstdint>

namespace databento::marketdata::normalized::dbn::v1 {

// The quantity of shares that are eligible to be matched at ref_price
struct PairedQty {

    static constexpr const char* name = "Paired Qty";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr PairedQty()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit PairedQty(const std::uint32_t value)
     : value{ value } {}

    // get value of PairedQty field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
