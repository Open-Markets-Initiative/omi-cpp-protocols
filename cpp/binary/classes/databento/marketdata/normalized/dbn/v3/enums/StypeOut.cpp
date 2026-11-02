#include "StypeOut.hpp"

namespace databento::marketdata::normalized::dbn::v3 {

std::string_view to_string(StypeOut value) {
    switch (value) {
        case StypeOut::InstrumentId: return "Instrument Id";
        case StypeOut::RawSymbol: return "Raw Symbol";
        case StypeOut::Smart: return "Smart";
        case StypeOut::Continuous: return "Continuous";
        case StypeOut::Parent: return "Parent";
        case StypeOut::NasdaqSymbol: return "Nasdaq Symbol";
        case StypeOut::CmsSymbol: return "Cms Symbol";
        case StypeOut::Isin: return "Isin";
        case StypeOut::UsCode: return "Us Code";
        case StypeOut::BbgCompId: return "Bbg Comp Id";
        case StypeOut::BbgCompTicker: return "Bbg Comp Ticker";
        case StypeOut::Figi: return "Figi";
        case StypeOut::FigiTicker: return "Figi Ticker";
        case StypeOut::ListingId: return "Listing Id";
        case StypeOut::IssuerId: return "Issuer Id";
        case StypeOut::SecurityId: return "Security Id";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, StypeOut value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace databento::marketdata::normalized::dbn::v3
