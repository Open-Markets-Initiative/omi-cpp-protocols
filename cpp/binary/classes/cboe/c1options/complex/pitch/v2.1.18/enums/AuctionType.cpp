#include "AuctionType.hpp"

namespace cboe::c1options::complex::pitch::v2_1_18 {

std::string_view to_string(AuctionType value) {
    switch (value) {
        case AuctionType::ComplexAuction: return "Complex Auction";
        case AuctionType::ComplexSolicitationAuction: return "Complex Solicitation Auction";
        case AuctionType::ComplexAim: return "Complex Aim";
        case AuctionType::CoaAllOrNone: return "Coa All Or None";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, AuctionType value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace cboe::c1options::complex::pitch::v2_1_18
