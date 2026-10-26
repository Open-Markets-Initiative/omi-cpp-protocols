#include "CustIndicator.hpp"

namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m {

std::string_view to_string(CustIndicator value) {
    switch (value) {
        case CustIndicator::Customer: return "Customer";
        case CustIndicator::Noncustomer: return "Noncustomer";
        case CustIndicator::DerivedForFutureUse: return "Derived For Future Use";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, CustIndicator value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m
