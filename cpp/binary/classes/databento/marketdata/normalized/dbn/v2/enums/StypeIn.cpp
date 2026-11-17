// Databento.MarketData.Normalized.Dbn.v2: enums/StypeIn.cpp
#include "StypeIn.hpp"

namespace databento::marketdata::normalized::dbn::v2 {

std::string_view to_string(StypeIn value) {
    switch (value) {
        case StypeIn::InstrumentId: return "Instrument Id";
        case StypeIn::RawSymbol: return "Raw Symbol";
        case StypeIn::Smart: return "Smart";
        case StypeIn::Continuous: return "Continuous";
        case StypeIn::Parent: return "Parent";
        case StypeIn::NasdaqSymbol: return "Nasdaq Symbol";
        case StypeIn::CmsSymbol: return "Cms Symbol";
        case StypeIn::Isin: return "Isin";
        case StypeIn::UsCode: return "Us Code";
        case StypeIn::BbgCompId: return "Bbg Comp Id";
        case StypeIn::BbgCompTicker: return "Bbg Comp Ticker";
        case StypeIn::Figi: return "Figi";
        case StypeIn::FigiTicker: return "Figi Ticker";
        case StypeIn::ListingId: return "Listing Id";
        case StypeIn::IssuerId: return "Issuer Id";
        case StypeIn::SecurityId: return "Security Id";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, StypeIn value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace databento::marketdata::normalized::dbn::v2
