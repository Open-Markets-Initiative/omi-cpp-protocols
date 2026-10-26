#include "SourceVenue.hpp"

namespace lseg::lse::level2mbo::gtp::v26_2 {

std::string_view to_string(SourceVenue value) {
    switch (value) {
        case SourceVenue::LondonStockExchange: return "London Stock Exchange";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, SourceVenue value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace lseg::lse::level2mbo::gtp::v26_2
