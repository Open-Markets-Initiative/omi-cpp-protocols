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
#include "../types/PriceQuoteCurrency.hpp"
#include "../types/MatchAlgorithm.hpp"
#include "../types/MinTradeVol.hpp"
#include "../types/MaxTradeVol.hpp"
#include "../types/MinPriceIncrementEx.hpp"
#include "../types/DisplayFactor.hpp"
#include "../types/PricePrecision.hpp"
#include "../types/UnitOfMeasure.hpp"
#include "../types/UnitOfMeasureQty.hpp"
#include "../types/HighLimitPrice.hpp"
#include "../types/LowLimitPrice.hpp"
#include "../types/MaxPriceVariation.hpp"
#include "../types/UserDefinedInstrument.hpp"
#include "../types/FinancialInstrumentFullName.hpp"
#include "../types/FxCurrencySymbol.hpp"
#include "../types/SettlType.hpp"
#include "../types/InterveningDays.hpp"
#include "../types/FxBenchmarkRateFix.hpp"
#include "../types/RateSource.hpp"
#include "../types/FixRateLocalTime.hpp"
#include "../types/FixRateLocalTimeZone.hpp"
#include "../types/MinQuoteLife.hpp"
#include "../types/MaxPriceDiscretionOffset.hpp"
#include "../types/InstrumentGuid.hpp"
#include "../structs/MaturityMonthYear.hpp"
#include "../types/SettlementLocale.hpp"
#include "../types/AltMinPriceIncrement.hpp"
#include "../types/AltMinQuoteLife.hpp"
#include "../types/AltPriceIncrementConstraint.hpp"
#include "../types/MaxBidAskConstraint.hpp"
#include "../structs/SimpleBinaryHeader.hpp"

namespace cme::mdp3::v13 {

#pragma pack(push, 1)

// MDInstrumentDefinitionFX
struct MdInstrumentDefinitionFx {

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
    PriceQuoteCurrency price_quote_currency;
    MatchAlgorithm match_algorithm;
    MinTradeVol min_trade_vol;
    MaxTradeVol max_trade_vol;
    MinPriceIncrementEx min_price_increment_ex;
    DisplayFactor display_factor;
    PricePrecision price_precision;
    UnitOfMeasure unit_of_measure;
    UnitOfMeasureQty unit_of_measure_qty;
    HighLimitPrice high_limit_price;
    LowLimitPrice low_limit_price;
    MaxPriceVariation max_price_variation;
    UserDefinedInstrument user_defined_instrument;
    FinancialInstrumentFullName financial_instrument_full_name;
    FxCurrencySymbol fx_currency_symbol;
    SettlType settl_type;
    InterveningDays intervening_days;
    FxBenchmarkRateFix fx_benchmark_rate_fix;
    RateSource rate_source;
    FixRateLocalTime fix_rate_local_time;
    FixRateLocalTimeZone fix_rate_local_time_zone;
    MinQuoteLife min_quote_life;
    MaxPriceDiscretionOffset max_price_discretion_offset;
    InstrumentGuid instrument_guid;
    MaturityMonthYear maturity_month_year;
    SettlementLocale settlement_locale;
    AltMinPriceIncrement alt_min_price_increment;
    AltMinQuoteLife alt_min_quote_life;
    AltPriceIncrementConstraint alt_price_increment_constraint;
    MaxBidAskConstraint max_bid_ask_constraint;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint16_t message_type = 63;

    // parse method
    static MdInstrumentDefinitionFx* parse(std::byte* buffer) {
        return reinterpret_cast<MdInstrumentDefinitionFx*>(buffer);
    }

    // parse method const
    static const MdInstrumentDefinitionFx* parse(const std::byte* buffer) {
        return reinterpret_cast<const MdInstrumentDefinitionFx*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const MdInstrumentDefinitionFx* parse(const SimpleBinaryHeader* header) {
        return reinterpret_cast<const MdInstrumentDefinitionFx*>(reinterpret_cast<const std::byte*>(header) + sizeof(SimpleBinaryHeader));
    }
};

#pragma pack(pop)
}
