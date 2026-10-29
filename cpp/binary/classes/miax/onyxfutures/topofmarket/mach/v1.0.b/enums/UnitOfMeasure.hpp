#pragma once

#include <string_view>

namespace miax::onyxfutures::topofmarket::mach::v1_0_b {

// Individual unit of the Deliverable of the Underlying Asset associated with the Futures
// Contract
// The field is text of more than one byte, so its codes are named constants rather than an enum
struct UnitOfMeasure {
    static constexpr std::string_view Bushels = "BU";        // Bushels
    static constexpr std::string_view PriceThenTime = "USD"; // Price Then Time

    // The documented name of a code, or empty for one the specification does not list
    static constexpr std::string_view describe(std::string_view code) {
        if (code == Bushels) { return "Bushels"; }
        if (code == PriceThenTime) { return "Price Then Time"; }
        return {};
    }
};

} // namespace miax::onyxfutures::topofmarket::mach::v1_0_b
