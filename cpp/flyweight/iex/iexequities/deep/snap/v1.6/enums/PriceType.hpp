#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace iex::iexequities::deep::snap::v1_6 {

// Price type identifier
enum class PriceType : char {
    IexOfficialOpeningPrice = 'Q', // Iex Official Opening Price
    IexOfficialClosingPrice = 'M', // Iex Official Closing Price
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(PriceType value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, PriceType value);

} // namespace iex::iexequities::deep::snap::v1_6
