#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace bse::bseindia::eobi::fbe::v1_4 {

// This field qualifies an instrument type on BSE.
enum class ProductComplex : std::uint8_t {
    FuturesSpread = 5, // Futures Spread
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(ProductComplex value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, ProductComplex value);

} // namespace bse::bseindia::eobi::fbe::v1_4
