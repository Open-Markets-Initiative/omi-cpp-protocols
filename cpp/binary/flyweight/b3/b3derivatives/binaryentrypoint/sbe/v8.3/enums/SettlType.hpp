#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3 {

// settlType
enum class SettlType : char {
    BuyersDiscretion = '0',  // Buyers Discretion
    SellersDiscretion = '8', // Sellers Discretion
    Mutual = 'X',            // Mutual
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(SettlType value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, SettlType value);

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3
