#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nasdaq::iseoptions::ordercombofeed::itch::v1_1 {

// ‘E’ = Exposure ‘C’ = Facilitation ‘S’ = Solicitation ‘P’ = PIM
enum class AuctionType : char {
    Exposure = 'E',     // Exposure
    Facilitation = 'C', // Facilitation
    Solicitation = 'S', // Solicitation
    Pim = 'P',          // Pim
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(AuctionType value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, AuctionType value);

} // namespace nasdaq::iseoptions::ordercombofeed::itch::v1_1
