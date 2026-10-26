#include "IndexValueDenominatorCode.hpp"

namespace siac::opra::output::obi::v6_2 {

std::string_view to_string(IndexValueDenominatorCode value) {
    switch (value) {
        case IndexValueDenominatorCode::Ten: return "Ten";
        case IndexValueDenominatorCode::Hundred: return "Hundred";
        case IndexValueDenominatorCode::Thousand: return "Thousand";
        case IndexValueDenominatorCode::TenThousand: return "Ten Thousand";
        case IndexValueDenominatorCode::HundredThousand: return "Hundred Thousand";
        case IndexValueDenominatorCode::Million: return "Million";
        case IndexValueDenominatorCode::TenMillion: return "Ten Million";
        case IndexValueDenominatorCode::NoFraction: return "No Fraction";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, IndexValueDenominatorCode value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace siac::opra::output::obi::v6_2
