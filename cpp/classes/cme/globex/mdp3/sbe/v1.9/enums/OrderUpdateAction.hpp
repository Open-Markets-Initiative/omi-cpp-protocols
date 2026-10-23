#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace cme::globex::mdp3::sbe::v1_9 {

// Order book update action to be applied to the order referenced by OrderID
enum class OrderUpdateAction : std::uint8_t {
    New = 0,    // New
    Update = 1, // Update
    Delete = 2, // Delete
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(OrderUpdateAction value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, OrderUpdateAction value);

} // namespace cme::globex::mdp3::sbe::v1_9
