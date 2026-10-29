#include "SecurityResponseType.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3 {

std::string_view to_string(SecurityResponseType value) {
    switch (value) {
        case SecurityResponseType::AcceptSecurityProposalAsIs: return "Accept Security Proposal As Is";
        case SecurityResponseType::RejectSecurityProposal: return "Reject Security Proposal";
        case SecurityResponseType::AcceptSecurityAsProposalWithRevisions: return "Accept Security As Proposal With Revisions";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, SecurityResponseType value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3
