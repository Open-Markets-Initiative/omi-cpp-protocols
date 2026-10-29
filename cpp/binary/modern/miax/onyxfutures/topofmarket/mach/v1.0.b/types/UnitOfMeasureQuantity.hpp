#pragma once

#include <cstddef>
#include <cstdint>

namespace miax::onyxfutures::topofmarket::mach::v1_0_b {

// The quantity of the Underlying Asset that is required for the Deliverable associated with the Futures Contract
struct UnitOfMeasureQuantity {

    static constexpr const char* name = "Unit Of Measure Quantity";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr UnitOfMeasureQuantity()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit UnitOfMeasureQuantity(const std::uint32_t value)
     : value{ value } {}

    // get value of UnitOfMeasureQuantity field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
