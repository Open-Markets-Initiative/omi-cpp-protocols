#include "SecurityExchange.hpp"

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

std::string_view to_string(SecurityExchange value) {
    switch (value) {
        case SecurityExchange::Cboe: return "Cboe";
        case SecurityExchange::OneChicagoNotSupported: return "One Chicago Not Supported";
        case SecurityExchange::CbsxNotSupported: return "Cbsx Not Supported";
        case SecurityExchange::Cfecof: return "Cfecof";
        case SecurityExchange::Cboe2Options: return "Cboe 2 Options";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, SecurityExchange value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace cboe::c1options::marketdatafeed::csm::v1_4_2
