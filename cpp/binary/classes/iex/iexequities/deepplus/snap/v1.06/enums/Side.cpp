#include "Side.hpp"

namespace iex::iexequities::deepplus::snap::v1_06 {

std::string_view to_string(Side value) {
    switch (value) {
        case Side::Buy: return "Buy";
        case Side::Sell: return "Sell";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, Side value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace iex::iexequities::deepplus::snap::v1_06
