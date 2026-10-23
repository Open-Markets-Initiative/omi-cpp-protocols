#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace siac::cqs::output::cta::v2_10_a {

// Identifies CQS as the originator of a message
enum class SipGeneratedMessageIdentifier : char {
    SipGeneratedMessageNotApplicable = ' ', // Sip Generated Message Not Applicable
    ConsolidatedQuotationSystem = 'S',      // Consolidated Quotation System
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(SipGeneratedMessageIdentifier value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, SipGeneratedMessageIdentifier value);

} // namespace siac::cqs::output::cta::v2_10_a
