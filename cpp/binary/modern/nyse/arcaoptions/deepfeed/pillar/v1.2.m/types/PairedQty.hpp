#pragma once

#include <cstddef>
#include <cstdint>

namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m {

// The number of contracts paired off at the Indicative Match Price.
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
