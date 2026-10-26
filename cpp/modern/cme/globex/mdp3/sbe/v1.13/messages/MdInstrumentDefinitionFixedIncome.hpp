#pragma once

#include "../bitfields/MatchEventIndicator.hpp"
#include "../types/TotNumReportsOptional.hpp"
#include "../types/SecurityUpdateAction.hpp"
#include "../types/LastUpdateTime.hpp"
#include "../types/MdSecurityTradingStatus.hpp"
#include "../types/ApplId.hpp"
#include "../types/MarketSegmentId.hpp"
#include "../types/UnderlyingProduct.hpp"
#include "../types/SecurityExchange.hpp"
#include "../types/SecurityGroup.hpp"
#include "../types/Asset.hpp"
#include "../types/Symbol.hpp"
#include "../types/SecurityId.hpp"
#include "../types/SecurityType.hpp"
#include "../types/CfiCode.hpp"
#include "../types/Currency.hpp"
#include "../types/SettlCurrency.hpp"
#include "../types/MatchAlgorithm.hpp"
#include "../types/MinTradeVol.hpp"
#include "../types/MaxTradeVol.hpp"
#include "../types/MinPriceIncrementOptionalEx.hpp"
#include "../types/DisplayFactor.hpp"
#include "../types/MainFraction.hpp"
#include "../types/SubFraction.hpp"
#include "../types/PriceDisplayFormat.hpp"
#include "../types/UnitOfMeasure.hpp"
#include "../types/UnitOfMeasureQty.hpp"
#include "../types/TradingReferencePrice.hpp"
#include "../types/TradingReferenceDate.hpp"
#include "../types/HighLimitPrice.hpp"
#include "../types/LowLimitPrice.hpp"
#include "../types/MaxPriceVariation.hpp"
#include "../types/MinPriceIncrementAmount.hpp"
#include "../types/IssueDate.hpp"
#include "../types/DatedDate.hpp"
#include "../types/MaturityDate.hpp"
#include "../types/CouponRate.hpp"
#include "../types/ParValue.hpp"
#include "../types/CouponFrequencyUnit.hpp"
#include "../types/CouponFrequencyPeriod.hpp"
#include "../types/CouponDayCount.hpp"
#include "../types/CountryOfIssue.hpp"
#include "../types/Issuer.hpp"
#include "../types/FinancialInstrumentFullName.hpp"
#include "../types/SecurityAltId.hpp"
#include "../types/SecurityAltIdSource.hpp"
#include "../types/PriceQuoteMethod.hpp"
#include "../types/PartyRoleClearingOrg.hpp"
#include "../types/UserDefinedInstrument.hpp"
#include "../types/RiskSet.hpp"
#include "../types/MarketSet.hpp"
#include "../types/InstrumentGuid.hpp"
#include "../structs/SimpleBinaryHeader.hpp"

namespace cme::mdp3::v13 {

#pragma pack(push, 1)

// MDInstrumentDefinitionFixedIncome
struct MdInstrumentDefinitionFixedIncome {

    MatchEventIndicator match_event_indicator;
    TotNumReportsOptional tot_num_reports_optional;
    SecurityUpdateAction security_update_action;
    LastUpdateTime last_update_time;
    MdSecurityTradingStatus md_security_trading_status;
    ApplId appl_id;
    MarketSegmentId market_segment_id;
    UnderlyingProduct underlying_product;
    SecurityExchange security_exchange;
    SecurityGroup security_group;
    Asset asset;
    Symbol symbol;
    SecurityId security_id;
    SecurityType security_type;
    CfiCode cfi_code;
    Currency currency;
    SettlCurrency settl_currency;
    MatchAlgorithm match_algorithm;
    MinTradeVol min_trade_vol;
    MaxTradeVol max_trade_vol;
    MinPriceIncrementOptionalEx min_price_increment_optional_ex;
    DisplayFactor display_factor;
    MainFraction main_fraction;
    SubFraction sub_fraction;
    PriceDisplayFormat price_display_format;
    UnitOfMeasure unit_of_measure;
    UnitOfMeasureQty unit_of_measure_qty;
    TradingReferencePrice trading_reference_price;
    TradingReferenceDate trading_reference_date;
    HighLimitPrice high_limit_price;
    LowLimitPrice low_limit_price;
    MaxPriceVariation max_price_variation;
    MinPriceIncrementAmount min_price_increment_amount;
    IssueDate issue_date;
    DatedDate dated_date;
    MaturityDate maturity_date;
    CouponRate coupon_rate;
    ParValue par_value;
    CouponFrequencyUnit coupon_frequency_unit;
    CouponFrequencyPeriod coupon_frequency_period;
    CouponDayCount coupon_day_count;
    CountryOfIssue country_of_issue;
    Issuer issuer;
    FinancialInstrumentFullName financial_instrument_full_name;
    SecurityAltId security_alt_id;
    SecurityAltIdSource security_alt_id_source;
    PriceQuoteMethod price_quote_method;
    PartyRoleClearingOrg party_role_clearing_org;
    UserDefinedInstrument user_defined_instrument;
    RiskSet risk_set;
    MarketSet market_set;
    InstrumentGuid instrument_guid;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint16_t message_type = 57;

    // parse method
    static MdInstrumentDefinitionFixedIncome* parse(std::byte* buffer) {
        return reinterpret_cast<MdInstrumentDefinitionFixedIncome*>(buffer);
    }

    // parse method const
    static const MdInstrumentDefinitionFixedIncome* parse(const std::byte* buffer) {
        return reinterpret_cast<const MdInstrumentDefinitionFixedIncome*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const MdInstrumentDefinitionFixedIncome* parse(const SimpleBinaryHeader* header) {
        return reinterpret_cast<const MdInstrumentDefinitionFixedIncome*>(reinterpret_cast<const std::byte*>(header) + sizeof(SimpleBinaryHeader));
    }
};

#pragma pack(pop)
}
