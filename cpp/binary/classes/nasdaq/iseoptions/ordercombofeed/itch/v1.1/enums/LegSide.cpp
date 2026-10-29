#include "LegSide.hpp"

namespace nasdaq::iseoptions::ordercombofeed::itch::v1_1 {

std::string_view to_string(LegSide value) {
    switch (value) {
        case LegSide::Buy: return "Buy";
        case LegSide::Sell: return "Sell";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, LegSide value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace nasdaq::iseoptions::ordercombofeed::itch::v1_1
