#pragma once

#include <cstddef>
#include <cstdint>

namespace cboe::edgaequities::multicastdepthofbook::pitch::v2_41_29 {

// Number of shares/contracts remaining after the execution
struct RemainingQuantity {

    static constexpr const char* name = "Remaining Quantity";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr RemainingQuantity()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit RemainingQuantity(const std::uint32_t value)
     : value{ value } {}

    // get value of RemainingQuantity field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
