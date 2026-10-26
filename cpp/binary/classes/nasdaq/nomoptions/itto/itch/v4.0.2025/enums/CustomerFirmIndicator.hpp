#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nasdaq::nomoptions::itto::itch::v4_0_2025 {

// For Order Exposure (AuctionType=I) only. Indicates the order capacity:
enum class CustomerFirmIndicator : char {
    Customer = 'C',                  // Customer
    FirmJoint = 'F',                 // Firm Joint
    Onfloor = 'M',                   // Onfloor
    Professional = 'P',              // Professional
    BrokerDealerNonRegistered = 'B', // Broker Dealer Non Registered
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(CustomerFirmIndicator value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, CustomerFirmIndicator value);

} // namespace nasdaq::nomoptions::itto::itch::v4_0_2025
