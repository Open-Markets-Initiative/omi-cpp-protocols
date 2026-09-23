#include "ShortSalePriceTestStatus.hpp"

namespace iex::iexequities::deepplus::snap::v1_06 {

std::string_view to_string(ShortSalePriceTestStatus value) {
    switch (value) {
        case ShortSalePriceTestStatus::NotInEffect: return "Not In Effect";
        case ShortSalePriceTestStatus::InEffect: return "In Effect";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, ShortSalePriceTestStatus value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace iex::iexequities::deepplus::snap::v1_06
