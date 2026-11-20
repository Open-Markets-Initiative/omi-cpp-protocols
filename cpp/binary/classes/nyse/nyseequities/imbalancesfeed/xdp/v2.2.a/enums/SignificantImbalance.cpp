// Nyse.NyseEquities.ImbalancesFeed.Xdp.v2.2.a: enums/SignificantImbalance.cpp
#include "SignificantImbalance.hpp"

namespace nyse::nyseequities::imbalancesfeed::xdp::v2_2_a {

std::string_view to_string(SignificantImbalance value) {
    switch (value) {
        case SignificantImbalance::NotSignificant: return "Not Significant";
        case SignificantImbalance::Significant: return "Significant";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, SignificantImbalance value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace nyse::nyseequities::imbalancesfeed::xdp::v2_2_a
