#include "OrderBookType.hpp"

namespace lseg::lse::level2mbo::gtp::v26_2 {

std::string_view to_string(OrderBookType value) {
    switch (value) {
        case OrderBookType::FirmQuoteBook: return "Firm Quote Book";
        case OrderBookType::Offbook: return "Offbook";
        case OrderBookType::ElectronicOrderBook: return "Electronic Order Book";
        case OrderBookType::PrivateRfq: return "Private Rfq";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, OrderBookType value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace lseg::lse::level2mbo::gtp::v26_2
