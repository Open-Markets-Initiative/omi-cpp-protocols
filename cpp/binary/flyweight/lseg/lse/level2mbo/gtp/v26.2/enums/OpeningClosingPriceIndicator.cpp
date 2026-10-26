#include "OpeningClosingPriceIndicator.hpp"

namespace lseg::lse::level2mbo::gtp::v26_2 {

std::string_view to_string(OpeningClosingPriceIndicator value) {
    switch (value) {
        case OpeningClosingPriceIndicator::Ut: return "Ut";
        case OpeningClosingPriceIndicator::At: return "At";
        case OpeningClosingPriceIndicator::MidOfBbo: return "Mid Of Bbo";
        case OpeningClosingPriceIndicator::LastAt: return "Last At";
        case OpeningClosingPriceIndicator::LastUt: return "Last Ut";
        case OpeningClosingPriceIndicator::Manual: return "Manual";
        case OpeningClosingPriceIndicator::PreviousClose: return "Previous Close";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, OpeningClosingPriceIndicator value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace lseg::lse::level2mbo::gtp::v26_2
