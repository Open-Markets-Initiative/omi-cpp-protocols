#include "TradeQualifier.hpp"

namespace lseg::lse::level2mbo::gtp::v26_2 {

std::string_view to_string(TradeQualifier value) {
    switch (value) {
        case TradeQualifier::Na: return "Na";
        case TradeQualifier::ClosingPriceCrossCpx: return "Closing Price Cross Cpx";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, TradeQualifier value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace lseg::lse::level2mbo::gtp::v26_2
