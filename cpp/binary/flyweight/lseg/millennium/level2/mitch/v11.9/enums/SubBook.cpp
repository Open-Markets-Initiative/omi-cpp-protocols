#include "SubBook.hpp"

namespace lseg::millennium::level2::mitch::v11_9 {

std::string_view to_string(SubBook value) {
    switch (value) {
        case SubBook::RegularTrades: return "Regular Trades";
        case SubBook::RfqTrades: return "Rfq Trades";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, SubBook value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace lseg::millennium::level2::mitch::v11_9
