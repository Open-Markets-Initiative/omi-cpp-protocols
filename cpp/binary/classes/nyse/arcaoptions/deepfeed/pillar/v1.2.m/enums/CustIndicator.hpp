#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m {

// Capacity of the order.
enum class CustIndicator : char {
    Customer = 'C',            // Customer
    NonCustomer = 'N',         // Non Customer
    DerivedForFutureUse = 'D', // Derived For Future Use
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(CustIndicator value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, CustIndicator value);

} // namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m
