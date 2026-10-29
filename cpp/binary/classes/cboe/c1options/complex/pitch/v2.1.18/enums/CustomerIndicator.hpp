#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace cboe::c1options::complex::pitch::v2_1_18 {

// Customer Indicator
enum class CustomerIndicator : char {
    NonCustomer = 'N', // Non Customer
    Customer = 'C',    // Customer
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(CustomerIndicator value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, CustomerIndicator value);

} // namespace cboe::c1options::complex::pitch::v2_1_18
