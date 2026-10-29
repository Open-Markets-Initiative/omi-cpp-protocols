#include "MarketCategory.hpp"

namespace nasdaq::nsmequities::totalview::itch::v4_0 {

std::string_view to_string(MarketCategory value) {
    switch (value) {
        case MarketCategory::Cqs: return "Cqs";
        case MarketCategory::NasdaqGlobalSelectMarket: return "Nasdaq Global Select Market";
        case MarketCategory::NasdaqGlobalMarket: return "Nasdaq Global Market";
        case MarketCategory::NasdaqCapitalMarket: return "Nasdaq Capital Market";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, MarketCategory value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace nasdaq::nsmequities::totalview::itch::v4_0
