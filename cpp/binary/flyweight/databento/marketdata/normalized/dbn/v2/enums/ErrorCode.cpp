#include "ErrorCode.hpp"

namespace databento::marketdata::normalized::dbn::v2 {

std::string_view to_string(ErrorCode value) {
    switch (value) {
        case ErrorCode::AuthFailed: return "Auth Failed";
        case ErrorCode::ApiKeyDeactivated: return "Api Key Deactivated";
        case ErrorCode::ConnectionLimitExceeded: return "Connection Limit Exceeded";
        case ErrorCode::SymbolResolutionFailed: return "Symbol Resolution Failed";
        case ErrorCode::InvalidSubscription: return "Invalid Subscription";
        case ErrorCode::InternalError: return "Internal Error";
        case ErrorCode::SkippedRecordsAfterSlowReading: return "Skipped Records After Slow Reading";
        case ErrorCode::ReplayDataAgedOut: return "Replay Data Aged Out";
        case ErrorCode::Unset: return "Unset";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, ErrorCode value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace databento::marketdata::normalized::dbn::v2
