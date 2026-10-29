#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nyse::arcaoptions::topfeed::pillar::v1_2_c {

// Customer or Firm capacity specified with the order. Values include:
enum class Capacity : char {
    NotSpecified = ' ',         // Not Specified
    Customer = '0',             // Customer
    Firm = '1',                 // Firm
    BrokerDealer = '2',         // Broker Dealer
    MarketMaker = '3',          // Market Maker
    ProfessionalCustomer = '8', // Professional Customer
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(Capacity value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, Capacity value);

} // namespace nyse::arcaoptions::topfeed::pillar::v1_2_c
