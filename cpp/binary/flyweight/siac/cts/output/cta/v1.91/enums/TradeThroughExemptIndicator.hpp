#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace siac::cts::output::cta::v1_91 {

// Denotes whether or not a trade is exempt (Rule 611) and when used jointly with certain Sale
// Conditions, will more fully describe the characteristics of a particular trade
enum class TradeThroughExemptIndicator : char {
    NotATradeThroughExemption = '0', // Not A Trade Through Exemption
    TradeThroughExemption = '1',     // Trade Through Exemption
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(TradeThroughExemptIndicator value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, TradeThroughExemptIndicator value);

} // namespace siac::cts::output::cta::v1_91
