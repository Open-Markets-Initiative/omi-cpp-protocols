#include "AuctionType.hpp"

namespace cboe::c1options::multicastdepthofbook::pitch::v2_39_4 {

std::string_view to_string(AuctionType value) {
    switch (value) {
        case AuctionType::Opening: return "Opening";
        case AuctionType::Closing: return "Closing";
        case AuctionType::Halt: return "Halt";
        case AuctionType::Ipo: return "Ipo";
        case AuctionType::Close: return "Close";
        case AuctionType::Sum: return "Sum";
        case AuctionType::Bam: return "Bam";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, AuctionType value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace cboe::c1options::multicastdepthofbook::pitch::v2_39_4
