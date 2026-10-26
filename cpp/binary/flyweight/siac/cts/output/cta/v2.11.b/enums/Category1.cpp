#include "Category1.hpp"

namespace siac::cts::output::cta::v2_11_b {

std::string_view to_string(Category1 value) {
    switch (value) {
        case Category1::RegularSettlement: return "Regular Settlement";
        case Category1::CashTradeSameDayClearing: return "Cash Trade Same Day Clearing";
        case Category1::Reserved: return "Reserved";
        case Category1::Seller: return "Seller";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, Category1 value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace siac::cts::output::cta::v2_11_b
