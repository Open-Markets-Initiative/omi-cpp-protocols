#pragma once

#include <string_view>

namespace asx::asxderivatives::ntp::itch::v1_05 {

// Participant identifier of the owner of the selling order. Blank for anonymous instruments.
// The field is text of more than one byte, so its codes are named constants rather than an enum
struct ParticipantIdSeller {
    static constexpr std::string_view Anonymous = "   "; // Anonymous

    // The documented name of a code, or empty for one the specification does not list
    static constexpr std::string_view describe(std::string_view code) {
        if (code == Anonymous) { return "Anonymous"; }
        return {};
    }
};

} // namespace asx::asxderivatives::ntp::itch::v1_05
