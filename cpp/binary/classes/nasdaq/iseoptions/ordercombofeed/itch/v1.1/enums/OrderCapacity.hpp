#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nasdaq::iseoptions::ordercombofeed::itch::v1_1 {

// Order Capacity value
enum class OrderCapacity : char {
    Customer = 'C',             // Customer
    CustomerProfessional = 'D', // Customer Professional
    Firm = 'F',                 // Firm
    BrokerDealerCustomer = 'B', // Broker Dealer Customer
    BrokerDealerFirm = 'K',     // Broker Dealer Firm
    Proprietary = 'E',          // Proprietary
    AwayMarketMaker = 'N',      // Away Market Maker
    MarketMaker = 'M',          // Market Maker
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(OrderCapacity value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, OrderCapacity value);

} // namespace nasdaq::iseoptions::ordercombofeed::itch::v1_1
