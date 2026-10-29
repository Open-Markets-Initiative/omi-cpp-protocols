#pragma once

#include <cstddef>
#include <cstdint>

namespace cboe::byxequities::multicastdepthofbook::pitch::v2_41_29 {

// Number of shares/contracts executed
struct ExecutedQuantity {

    static constexpr const char* name = "Executed Quantity";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr ExecutedQuantity()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit ExecutedQuantity(const std::uint32_t value)
     : value{ value } {}

    // get value of ExecutedQuantity field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
