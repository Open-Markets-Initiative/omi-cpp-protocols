#include "ImbalanceSide.hpp"

namespace iex::iexequities::deep::iextp::v1_06 {

std::string_view to_string(ImbalanceSide value) {
    switch (value) {
        case ImbalanceSide::Buy: return "Buy";
        case ImbalanceSide::Sell: return "Sell";
        case ImbalanceSide::None: return "None";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, ImbalanceSide value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace iex::iexequities::deep::iextp::v1_06
