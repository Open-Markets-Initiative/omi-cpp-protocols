#pragma once

#include <cstddef>
#include <cstdint>

namespace lseg::millennium::level2::mitch::v11_9 {

// New displayed quantity of the order.
struct NewQuantity {

    static constexpr const char* name = "New Quantity";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr NewQuantity()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit NewQuantity(const std::uint32_t value)
     : value{ value } {}

    // get value of NewQuantity field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
