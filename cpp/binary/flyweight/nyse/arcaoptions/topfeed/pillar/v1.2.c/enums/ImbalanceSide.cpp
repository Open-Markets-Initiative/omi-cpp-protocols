#include "ImbalanceSide.hpp"

namespace nyse::arcaoptions::topfeed::pillar::v1_2_c {

std::string_view to_string(ImbalanceSide value) {
    switch (value) {
        case ImbalanceSide::Buy: return "Buy";
        case ImbalanceSide::Sell: return "Sell";
        case ImbalanceSide::NoImbalance: return "No Imbalance";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, ImbalanceSide value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace nyse::arcaoptions::topfeed::pillar::v1_2_c
