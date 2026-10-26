#include "Capacity.hpp"

namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m {

std::string_view to_string(Capacity value) {
    switch (value) {
        case Capacity::NaSpaceOr0X20: return "Na Space Or 0 X 20";
        case Capacity::Customer: return "Customer";
        case Capacity::Firm: return "Firm";
        case Capacity::BrokerDealer: return "Broker Dealer";
        case Capacity::MarketMaker: return "Market Maker";
        case Capacity::AwayMarketMaker: return "Away Market Maker";
        case Capacity::ProfessionalCustomer: return "Professional Customer";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, Capacity value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m
