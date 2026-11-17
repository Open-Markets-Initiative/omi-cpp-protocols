// Databento.MarketData.Normalized.Dbn.v3: enums/ErrorCode.hpp
#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace databento::marketdata::normalized::dbn::v3 {

// The error code
enum class ErrorCode : std::uint8_t {
    AuthFailed = 1,                     // Auth Failed
    ApiKeyDeactivated = 2,              // Api Key Deactivated
    ConnectionLimitExceeded = 3,        // Connection Limit Exceeded
    SymbolResolutionFailed = 4,         // Symbol Resolution Failed
    InvalidSubscription = 5,            // Invalid Subscription
    InternalError = 6,                  // Internal Error
    SkippedRecordsAfterSlowReading = 7, // Skipped Records After Slow Reading
    ReplayDataAgedOut = 8,              // Replay Data Aged Out
    Unset = 255,                        // Unset
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(ErrorCode value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, ErrorCode value);

} // namespace databento::marketdata::normalized::dbn::v3
