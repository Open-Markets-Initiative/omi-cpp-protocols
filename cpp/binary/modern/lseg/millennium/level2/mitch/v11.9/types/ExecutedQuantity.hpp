#pragma once

#include <cstddef>
#include <cstdint>

namespace lseg::millennium::level2::mitch::v11_9 {

// Quantity executed.
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
