#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace eurex::t7::eobi::fbe::v15_0 {

enum class RelatedPriceType : std::uint8_t {
    Basis = 1,                 // Basis
    CustomUnderlyingPrice = 2, // Custom Underlying Price
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(RelatedPriceType value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, RelatedPriceType value);

} // namespace eurex::t7::eobi::fbe::v15_0
