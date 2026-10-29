#include "LegalMarket.hpp"

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

std::string_view to_string(LegalMarket value) {
    switch (value) {
        case LegalMarket::NotALegalMarket: return "Not A Legal Market";
        case LegalMarket::LegalMarket: return "Legal Market";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, LegalMarket value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace cboe::c1options::marketdatafeed::csm::v1_4_2
