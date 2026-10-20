#include "Detail.hpp"

namespace iex::iexequities::deepplus::iextp::v1_05 {

std::string_view to_string(Detail value) {
    switch (value) {
        case Detail::NoPriceTestInPlace: return "No Price Test In Place";
        case Detail::ShortSalePriceTestRestrictionInEffectDueToAnIntradayPriceDropInTheSecurity: return "Short Sale Price Test Restriction In Effect Due To An Intraday Price Drop In The Security";
        case Detail::ShortSalePriceTestRestrictionRemainsInEffectFromPriorDay: return "Short Sale Price Test Restriction Remains In Effect From Prior Day";
        case Detail::ShortSalePriceTestRestrictionDeactivated: return "Short Sale Price Test Restriction Deactivated";
        case Detail::NotAvailable: return "Not Available";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, Detail value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace iex::iexequities::deepplus::iextp::v1_05
