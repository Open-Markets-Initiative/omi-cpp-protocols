#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace b3::b3derivatives::binaryumdf::sbe::v2_2 {

// Attribute value appropriate to the InstrAttribType (871) field.
enum class InstrAttribValue : std::uint8_t {
    ElectronicMatchOrGtdGtcEligible = 1, // Electronic Match Or Gtd Gtc Eligible
    OrderCrossEligible = 2,              // Order Cross Eligible
    BlockTradeEligible = 3,              // Block Trade Eligible
    FlagRfqForCrossEligible = 14,        // Flag Rfq For Cross Eligible
    NegotiatedQuoteEligible = 17,        // Negotiated Quote Eligible
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(InstrAttribValue value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, InstrAttribValue value);

} // namespace b3::b3derivatives::binaryumdf::sbe::v2_2
