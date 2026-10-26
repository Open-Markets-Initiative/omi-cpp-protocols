#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace b3::b3derivatives::binaryumdf::sbe::v2_1 {

// newsSource
enum class NewsSource : std::uint8_t {
    Other = 0,                       // Other
    Dcm = 1,                         // Dcm
    Bbmnet = 2,                      // Bbmnet
    MarketSurveillance = 3,          // Market Surveillance
    Internet = 4,                    // Internet
    DprVe = 5,                       // Dpr Ve
    MktOpsFxAgency = 19,             // Mkt Ops Fx Agency
    MktOpsDerivativesAgency = 20,    // Mkt Ops Derivatives Agency
    OverTheCounterNewsAgency = 11,   // Over The Counter News Agency
    ElectronicPurchaseExchange = 13, // Electronic Purchase Exchange
    CblcNewsAgency = 14,             // Cblc News Agency
    BovespaIndexAgency = 15,         // Bovespa Index Agency
    BovespaInstitutionalAgency = 16, // Bovespa Institutional Agency
    MktOpsEquitiesAgency = 17,       // Mkt Ops Equities Agency
    BovespaCompaniesAgency = 18,     // Bovespa Companies Agency
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(NewsSource value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, NewsSource value);

} // namespace b3::b3derivatives::binaryumdf::sbe::v2_1
