#include "ReportingStatus.hpp"

namespace otcmarkets::linkats::multicast::link::v4_3 {

std::string_view to_string(ReportingStatus value) {
    switch (value) {
        case ReportingStatus::AlternativeReporting: return "Alternative Reporting";
        case ReportingStatus::BankThrift: return "Bank Thrift";
        case ReportingStatus::SecReporting: return "Sec Reporting";
        case ReportingStatus::InternationalReporting: return "International Reporting";
        case ReportingStatus::InsuranceCompany: return "Insurance Company";
        case ReportingStatus::NoReporting: return "No Reporting";
        case ReportingStatus::OtherReporting: return "Other Reporting";
        case ReportingStatus::FinraReporting: return "Finra Reporting";
        case ReportingStatus::SecInvestmentCompany: return "Sec Investment Company";
        case ReportingStatus::SecRegA: return "Sec Reg A";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, ReportingStatus value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace otcmarkets::linkats::multicast::link::v4_3
