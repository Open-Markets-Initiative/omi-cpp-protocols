#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nasdaq::nordicequities::totalview::itch::v3_04_x {

// Where a non displayed order has been executed
enum class TradeType : char {
    MainBook = 'B',  // Main Book
    NordicMid = 'S', // Nordic Mid
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(TradeType value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, TradeType value);

} // namespace nasdaq::nordicequities::totalview::itch::v3_04_x
