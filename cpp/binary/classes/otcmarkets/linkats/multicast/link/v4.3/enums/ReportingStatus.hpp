#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace otcmarkets::linkats::multicast::link::v4_3 {

// Reporting status.
enum class ReportingStatus : char {
    AlternativeReporting = 'A',   // Alternative Reporting
    BankThrift = 'B',             // Bank Thrift
    SecReporting = 'F',           // Sec Reporting
    InternationalReporting = 'G', // International Reporting
    InsuranceCompany = 'I',       // Insurance Company
    NoReporting = 'N',            // No Reporting
    OtherReporting = 'O',         // Other Reporting
    FinraReporting = 'R',         // Finra Reporting
    SecInvestmentCompany = 'V',   // Sec Investment Company
    SecRegA = 'W',                // Sec Reg A
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(ReportingStatus value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, ReportingStatus value);

} // namespace otcmarkets::linkats::multicast::link::v4_3
