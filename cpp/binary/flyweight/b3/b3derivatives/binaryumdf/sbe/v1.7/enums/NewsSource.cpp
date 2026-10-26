#include "NewsSource.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v1_7 {

std::string_view to_string(NewsSource value) {
    switch (value) {
        case NewsSource::Other: return "Other";
        case NewsSource::Dcm: return "Dcm";
        case NewsSource::Bbmnet: return "Bbmnet";
        case NewsSource::MarketSurveillance: return "Market Surveillance";
        case NewsSource::Internet: return "Internet";
        case NewsSource::DprVe: return "Dpr Ve";
        case NewsSource::MktOpsFxAgency: return "Mkt Ops Fx Agency";
        case NewsSource::MktOpsDerivativesAgency: return "Mkt Ops Derivatives Agency";
        case NewsSource::OverTheCounterNewsAgency: return "Over The Counter News Agency";
        case NewsSource::ElectronicPurchaseExchange: return "Electronic Purchase Exchange";
        case NewsSource::CblcNewsAgency: return "Cblc News Agency";
        case NewsSource::BovespaIndexAgency: return "Bovespa Index Agency";
        case NewsSource::BovespaInstitutionalAgency: return "Bovespa Institutional Agency";
        case NewsSource::MktOpsEquitiesAgency: return "Mkt Ops Equities Agency";
        case NewsSource::BovespaCompaniesAgency: return "Bovespa Companies Agency";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, NewsSource value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace b3::b3derivatives::binaryumdf::sbe::v1_7
