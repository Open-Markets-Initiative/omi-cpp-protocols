#pragma once

#include <string_view>

namespace asx::asxderivatives::ntp::itch::v1_05 {

// Selling participant identifier of the owner of the aggressive order.
// The field is text of more than one byte, so its codes are named constants rather than an enum
struct SellerParticipantId {
    static constexpr std::string_view Anonymous = "   "; // Anonymous

    // The documented name of a code, or empty for one the specification does not list
    static constexpr std::string_view describe(std::string_view code) {
        if (code == Anonymous) { return "Anonymous"; }
        return {};
    }
};

} // namespace asx::asxderivatives::ntp::itch::v1_05
