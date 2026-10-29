#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace jnx::jnxequities::pts::itch::v1_6 {

// Current short selling price restriction state.
enum class ShortSellingState : char {
    NoPriceRestriction = '0',       // No Price Restriction
    PriceRestrictionInEffect = '1', // Price Restriction In Effect
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(ShortSellingState value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, ShortSellingState value);

} // namespace jnx::jnxequities::pts::itch::v1_6
