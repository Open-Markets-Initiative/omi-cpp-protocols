#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace lseg::lse::level2mbo::gtp::v26_2 {

// For London Stock Exchange, during continuous trading and CPX session, 1[2] will be sent for
// execution of visible[hidden] quantities. For London Stock Exchange Auction Trades, 0 will be
// sent indicating 'Not Applicable' (N/A).
enum class HiddenExecutionIndicator : std::uint8_t {
    Na = 0,      // Na
    Visible = 1, // Visible
    Hidden = 2,  // Hidden
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(HiddenExecutionIndicator value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, HiddenExecutionIndicator value);

} // namespace lseg::lse::level2mbo::gtp::v26_2
