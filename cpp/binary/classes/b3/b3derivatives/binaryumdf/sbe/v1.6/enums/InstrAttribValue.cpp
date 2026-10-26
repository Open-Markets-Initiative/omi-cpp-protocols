#include "InstrAttribValue.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v1_6 {

std::string_view to_string(InstrAttribValue value) {
    switch (value) {
        case InstrAttribValue::ElectronicMatchOrGtdGtcEligible: return "Electronic Match Or Gtd Gtc Eligible";
        case InstrAttribValue::OrderCrossEligible: return "Order Cross Eligible";
        case InstrAttribValue::BlockTradeEligible: return "Block Trade Eligible";
        case InstrAttribValue::FlagRfqForCrossEligible: return "Flag Rfq For Cross Eligible";
        case InstrAttribValue::NegotiatedQuoteEligible: return "Negotiated Quote Eligible";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, InstrAttribValue value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace b3::b3derivatives::binaryumdf::sbe::v1_6
