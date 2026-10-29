#include "OrderCapacity.hpp"

namespace nasdaq::iseoptions::ordercombofeed::itch::v1_1 {

std::string_view to_string(OrderCapacity value) {
    switch (value) {
        case OrderCapacity::Customer: return "Customer";
        case OrderCapacity::CustomerProfessional: return "Customer Professional";
        case OrderCapacity::Firm: return "Firm";
        case OrderCapacity::BrokerDealerCustomer: return "Broker Dealer Customer";
        case OrderCapacity::BrokerDealerFirm: return "Broker Dealer Firm";
        case OrderCapacity::Proprietary: return "Proprietary";
        case OrderCapacity::AwayMarketMaker: return "Away Market Maker";
        case OrderCapacity::MarketMaker: return "Market Maker";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, OrderCapacity value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace nasdaq::iseoptions::ordercombofeed::itch::v1_1
