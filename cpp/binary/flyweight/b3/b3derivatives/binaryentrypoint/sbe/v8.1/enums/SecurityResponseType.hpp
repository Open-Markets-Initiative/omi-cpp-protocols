#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1 {

// securityResponseType
enum class SecurityResponseType : std::uint8_t {
    AcceptSecurityProposalAsIs = 1,            // Accept Security Proposal As Is
    RejectSecurityProposal = 5,                // Reject Security Proposal
    AcceptSecurityAsProposalWithRevisions = 2, // Accept Security As Proposal With Revisions
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(SecurityResponseType value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, SecurityResponseType value);

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1
