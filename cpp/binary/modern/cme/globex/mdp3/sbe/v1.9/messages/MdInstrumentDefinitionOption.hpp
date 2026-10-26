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
#include "../types/PutOrCall.hpp"
#include "../structs/MaturityMonthYear.hpp"
#include "../types/Currency.hpp"
#include "../types/StrikePriceEx.hpp"
#include "../types/StrikeCurrency.hpp"
#include "../types/SettlCurrency.hpp"
#include "../types/MinCabPriceEx.hpp"
#include "../types/MatchAlgorithm.hpp"
#include "../types/MinTradeVol.hpp"
#include "../types/MaxTradeVol.hpp"
#include "../types/MinPriceIncrementOptionalEx.hpp"
#include "../types/MinPriceIncrementAmountEx.hpp"
#include "../types/DisplayFactorEx.hpp"
#include "../types/TickRule.hpp"
#include "../types/MainFraction.hpp"
#include "../types/SubFraction.hpp"
#include "../types/PriceDisplayFormat.hpp"
#include "../types/UnitOfMeasure.hpp"
#include "../types/UnitOfMeasureQtyEx.hpp"
#include "../types/TradingReferencePriceEx.hpp"
#include "../bitfields/SettlPriceType.hpp"
#include "../types/ClearedVolume.hpp"
#include "../types/OpenInterestQty.hpp"
#include "../types/LowLimitPriceEx.hpp"
#include "../types/HighLimitPriceEx.hpp"
#include "../types/UserDefinedInstrument.hpp"
#include "../types/TradingReferenceDate.hpp"
#include "../structs/SimpleBinaryHeader.hpp"

namespace cme::mdp3::v9 {

#pragma pack(push, 1)

// MDInstrumentDefinitionOption
struct MdInstrumentDefinitionOption {

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
    PutOrCall put_or_call;
    MaturityMonthYear maturity_month_year;
    Currency currency;
    StrikePriceEx strike_price_ex;
    StrikeCurrency strike_currency;
    SettlCurrency settl_currency;
    MinCabPriceEx min_cab_price_ex;
    MatchAlgorithm match_algorithm;
    MinTradeVol min_trade_vol;
    MaxTradeVol max_trade_vol;
    MinPriceIncrementOptionalEx min_price_increment_optional_ex;
    MinPriceIncrementAmountEx min_price_increment_amount_ex;
    DisplayFactorEx display_factor_ex;
    TickRule tick_rule;
    MainFraction main_fraction;
    SubFraction sub_fraction;
    PriceDisplayFormat price_display_format;
    UnitOfMeasure unit_of_measure;
    UnitOfMeasureQtyEx unit_of_measure_qty_ex;
    TradingReferencePriceEx trading_reference_price_ex;
    SettlPriceType settl_price_type;
    ClearedVolume cleared_volume;
    OpenInterestQty open_interest_qty;
    LowLimitPriceEx low_limit_price_ex;
    HighLimitPriceEx high_limit_price_ex;
    UserDefinedInstrument user_defined_instrument;
    TradingReferenceDate trading_reference_date;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint16_t message_type = 55;

    // parse method
    static MdInstrumentDefinitionOption* parse(std::byte* buffer) {
        return reinterpret_cast<MdInstrumentDefinitionOption*>(buffer);
    }

    // parse method const
    static const MdInstrumentDefinitionOption* parse(const std::byte* buffer) {
        return reinterpret_cast<const MdInstrumentDefinitionOption*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const MdInstrumentDefinitionOption* parse(const SimpleBinaryHeader* header) {
        return reinterpret_cast<const MdInstrumentDefinitionOption*>(reinterpret_cast<const std::byte*>(header) + sizeof(SimpleBinaryHeader));
    }
};

#pragma pack(pop)
}
