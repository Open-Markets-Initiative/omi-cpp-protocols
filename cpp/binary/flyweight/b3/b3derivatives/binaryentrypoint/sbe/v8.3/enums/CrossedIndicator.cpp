#include "CrossedIndicator.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3 {

std::string_view to_string(CrossedIndicator value) {
    switch (value) {
        case CrossedIndicator::StructuredTransaction: return "Structured Transaction";
        case CrossedIndicator::OperationalError: return "Operational Error";
        case CrossedIndicator::TwapVwap: return "Twap Vwap";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, CrossedIndicator value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3
