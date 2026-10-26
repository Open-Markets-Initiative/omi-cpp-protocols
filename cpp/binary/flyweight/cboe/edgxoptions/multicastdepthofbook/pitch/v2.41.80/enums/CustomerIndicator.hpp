#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace cboe::edgxoptions::multicastdepthofbook::pitch::v2_41_80 {

// BZX/C1/EDGX Options Only (space filled on C2 Options and all equities markets). N =
// Non-Customer, C = Customer, R = Retail Priority order (EDGX Equities only).
enum class CustomerIndicator : char {
    NonCustomer = 'N',         // Non Customer
    Customer = 'C',            // Customer
    RetailPriorityOrder = 'R', // Retail Priority Order
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(CustomerIndicator value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, CustomerIndicator value);

} // namespace cboe::edgxoptions::multicastdepthofbook::pitch::v2_41_80
