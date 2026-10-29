#include "SaleConditionCategory.hpp"

namespace siac::cts::output::cta::v2_9 {

std::string_view to_string(SaleConditionCategory value) {
    switch (value) {
        case SaleConditionCategory::NotApplicable: return "Not Applicable";
        case SaleConditionCategory::Category1: return "Category 1";
        case SaleConditionCategory::Category2: return "Category 2";
        case SaleConditionCategory::Category3: return "Category 3";
        case SaleConditionCategory::Category4: return "Category 4";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, SaleConditionCategory value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace siac::cts::output::cta::v2_9
