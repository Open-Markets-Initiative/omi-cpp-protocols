#include "PriceType.hpp"

namespace iex::iexequities::tops::iextp::v1_66 {

std::string_view to_string(PriceType value) {
    switch (value) {
        case PriceType::IexOfficialOpeningPrice: return "Iex Official Opening Price";
        case PriceType::IexOfficialClosingPrice: return "Iex Official Closing Price";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, PriceType value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace iex::iexequities::tops::iextp::v1_66
