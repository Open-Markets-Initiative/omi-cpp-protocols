#include "OpenClosePriceIndicator.hpp"

namespace lseg::millennium::level2::mitch::v11_9 {

std::string_view to_string(OpenClosePriceIndicator value) {
    switch (value) {
        case OpenClosePriceIndicator::Ut: return "Ut";
        case OpenClosePriceIndicator::At: return "At";
        case OpenClosePriceIndicator::MidOfBbo: return "Mid Of Bbo";
        case OpenClosePriceIndicator::LastAt: return "Last At";
        case OpenClosePriceIndicator::LastUt: return "Last Ut";
        case OpenClosePriceIndicator::Manual: return "Manual";
        case OpenClosePriceIndicator::DerivedFromPreviousClose: return "Derived From Previous Close";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, OpenClosePriceIndicator value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace lseg::millennium::level2::mitch::v11_9
