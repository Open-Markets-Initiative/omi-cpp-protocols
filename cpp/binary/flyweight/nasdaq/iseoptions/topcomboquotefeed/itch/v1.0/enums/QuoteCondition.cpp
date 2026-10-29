#include "QuoteCondition.hpp"

namespace nasdaq::iseoptions::topcomboquotefeed::itch::v1_0 {

std::string_view to_string(QuoteCondition value) {
    switch (value) {
        case QuoteCondition::RegularQuote: return "Regular Quote";
        case QuoteCondition::Halted: return "Halted";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, QuoteCondition value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace nasdaq::iseoptions::topcomboquotefeed::itch::v1_0
