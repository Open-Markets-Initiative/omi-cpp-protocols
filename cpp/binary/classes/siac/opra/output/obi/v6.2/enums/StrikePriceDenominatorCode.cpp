#include "StrikePriceDenominatorCode.hpp"

namespace siac::opra::output::obi::v6_2 {

std::string_view to_string(StrikePriceDenominatorCode value) {
    switch (value) {
        case StrikePriceDenominatorCode::Ten: return "Ten";
        case StrikePriceDenominatorCode::Hundred: return "Hundred";
        case StrikePriceDenominatorCode::Thousand: return "Thousand";
        case StrikePriceDenominatorCode::TenThousand: return "Ten Thousand";
        case StrikePriceDenominatorCode::HundredThousand: return "Hundred Thousand";
        case StrikePriceDenominatorCode::NoFraction: return "No Fraction";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, StrikePriceDenominatorCode value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace siac::opra::output::obi::v6_2
