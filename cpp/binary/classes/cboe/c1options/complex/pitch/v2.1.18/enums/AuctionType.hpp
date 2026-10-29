#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace cboe::c1options::complex::pitch::v2_1_18 {

// Auction Type
enum class AuctionType : char {
    ComplexAuction = 'C',             // Complex Auction
    ComplexSolicitationAuction = 'S', // Complex Solicitation Auction
    ComplexAim = 'B',                 // Complex Aim
    CoaAllOrNone = 'O',               // Coa All Or None
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(AuctionType value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, AuctionType value);

} // namespace cboe::c1options::complex::pitch::v2_1_18
