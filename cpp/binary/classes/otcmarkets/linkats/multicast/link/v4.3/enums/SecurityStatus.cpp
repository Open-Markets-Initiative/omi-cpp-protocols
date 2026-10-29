#include "SecurityStatus.hpp"

namespace otcmarkets::linkats::multicast::link::v4_3 {

std::string_view to_string(SecurityStatus value) {
    switch (value) {
        case SecurityStatus::Active: return "Active";
        case SecurityStatus::QuoteOnly: return "Quote Only";
        case SecurityStatus::Suspended: return "Suspended";
        case SecurityStatus::Halted: return "Halted";
        case SecurityStatus::InternalHalt: return "Internal Halt";
        case SecurityStatus::Revoked: return "Revoked";
        case SecurityStatus::Deleted: return "Deleted";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, SecurityStatus value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace otcmarkets::linkats::multicast::link::v4_3
