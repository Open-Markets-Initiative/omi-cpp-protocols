#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace lseg::lse::level2mbo::gtp::v26_2 {

// Order book the status applies to.
enum class OrderBookType : std::uint8_t {
    FirmQuoteBook = 1,       // Firm Quote Book
    Offbook = 2,             // Offbook
    ElectronicOrderBook = 3, // Electronic Order Book
    PrivateRfq = 4,          // Private Rfq
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(OrderBookType value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, OrderBookType value);

} // namespace lseg::lse::level2mbo::gtp::v26_2
