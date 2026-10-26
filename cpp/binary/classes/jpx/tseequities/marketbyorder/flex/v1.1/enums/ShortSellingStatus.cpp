#include "ShortSellingStatus.hpp"

namespace jpx::tseequities::marketbyorder::flex::v1_1 {

std::string_view to_string(ShortSellingStatus value) {
    switch (value) {
        case ShortSellingStatus::ShortSellingRegulationIsNotApplied: return "Short Selling Regulation Is Not Applied";
        case ShortSellingStatus::ShortSellingRegulationIsApplied: return "Short Selling Regulation Is Applied";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, ShortSellingStatus value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace jpx::tseequities::marketbyorder::flex::v1_1
