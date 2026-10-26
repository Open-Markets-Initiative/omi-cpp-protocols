#pragma once

#include <cstddef>
#include <cstdint>

namespace lseg::millennium::level2::mitch::v11_9 {

// Displayed quantity of the order after the execution.
struct DisplayQuantity {

    static constexpr const char* name = "Display Quantity";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr DisplayQuantity()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit DisplayQuantity(const std::uint32_t value)
     : value{ value } {}

    // get value of DisplayQuantity field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
