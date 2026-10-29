#include "AuctionOpeningType.hpp"

namespace cboe::c1options::complex::pitch::v2_1_18 {

std::string_view to_string(AuctionOpeningType value) {
    switch (value) {
        case AuctionOpeningType::Gth: return "Gth";
        case AuctionOpeningType::Rth: return "Rth";
        case AuctionOpeningType::HaltReopening: return "Halt Reopening";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, AuctionOpeningType value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace cboe::c1options::complex::pitch::v2_1_18
