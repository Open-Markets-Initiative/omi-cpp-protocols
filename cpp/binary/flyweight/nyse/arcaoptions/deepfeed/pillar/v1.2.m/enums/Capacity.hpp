#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m {

// Customer or Firm capacity specified with the order. Only valid for BOLD (Type = B).
enum class Capacity : char {
    NaSpaceOr0X20 = ' ',        // Na Space Or 0 X 20
    Customer = '0',             // Customer
    Firm = '1',                 // Firm
    BrokerDealer = '2',         // Broker Dealer
    MarketMaker = '3',          // Market Maker
    AwayMarketMaker = '5',      // Away Market Maker
    ProfessionalCustomer = '8', // Professional Customer
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(Capacity value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, Capacity value);

} // namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m
