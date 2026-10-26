#pragma once

#include <cstddef>
#include <cstdint>

namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m {

// The total imbalance quantity at the Indicative Match Price.
struct TotalImbalanceQty {

    static constexpr const char* name = "Total Imbalance Qty";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr TotalImbalanceQty()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit TotalImbalanceQty(const std::uint32_t value)
     : value{ value } {}

    // get value of TotalImbalanceQty field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
