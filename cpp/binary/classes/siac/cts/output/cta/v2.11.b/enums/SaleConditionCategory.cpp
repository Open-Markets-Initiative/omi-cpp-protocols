#include "SaleConditionCategory.hpp"

namespace siac::cts::output::cta::v2_11_b {

std::string_view to_string(SaleConditionCategory value) {
    switch (value) {
        case SaleConditionCategory::SaleConditionCategoryNotApplicable: return "Sale Condition Category Not Applicable";
        case SaleConditionCategory::SaleConditionCategory1: return "Sale Condition Category 1";
        case SaleConditionCategory::SaleConditionCategory2: return "Sale Condition Category 2";
        case SaleConditionCategory::SaleConditionCategory3: return "Sale Condition Category 3";
        case SaleConditionCategory::SaleConditionCategory4: return "Sale Condition Category 4";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, SaleConditionCategory value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace siac::cts::output::cta::v2_11_b
