#pragma once

#include <cstddef>
#include <cstdint>

namespace lseg::millennium::level2::mitch::v11_9 {

// Quantity that will be matched at the indicative price.
struct PairedQuantity {

    static constexpr const char* name = "Paired Quantity";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr PairedQuantity()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit PairedQuantity(const std::uint32_t value)
     : value{ value } {}

    // get value of PairedQuantity field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
