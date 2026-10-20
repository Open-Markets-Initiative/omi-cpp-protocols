#include "Detail.hpp"

namespace iex::iexequities::tops::iextp::v1_66 {

std::string_view to_string(Detail value) {
    switch (value) {
        case Detail::NoPriceTestInPlace: return "No Price Test In Place";
        case Detail::Activated: return "Activated";
        case Detail::Continued: return "Continued";
        case Detail::Deactivated: return "Deactivated";
        case Detail::NotAvailable: return "Not Available";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, Detail value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace iex::iexequities::tops::iextp::v1_66
