#pragma once

#include "../bitfields/MatchEventIndicator.hpp"
#include "../types/TotNumReportsOptional.hpp"
#include "../types/SecurityUpdateAction.hpp"
#include "../types/LastUpdateTime.hpp"
#include "../types/MdSecurityTradingStatus.hpp"
#include "../types/ApplId.hpp"
#include "../types/MarketSegmentId.hpp"
#include "../types/UnderlyingProductOptional.hpp"
#include "../types/SecurityExchange.hpp"
#include "../types/SecurityGroup.hpp"
#include "../types/Asset.hpp"
#include "../types/Symbol.hpp"
#include "../types/SecurityId.hpp"
#include "../types/SecurityType.hpp"
#include "../types/CfiCode.hpp"
#include "../structs/MaturityMonthYear.hpp"
#include "../types/Currency.hpp"
#include "../types/SecuritySubType.hpp"
#include "../types/UserDefinedInstrument.hpp"
#include "../types/MatchAlgorithm.hpp"
#include "../types/MinTradeVol.hpp"
#include "../types/MaxTradeVol.hpp"
#include "../types/MinPriceIncrementOptionalEx.hpp"
#include "../types/DisplayFactorEx.hpp"
#include "../types/PriceDisplayFormat.hpp"
#include "../types/PriceRatioEx.hpp"
#include "../types/TickRule.hpp"
#include "../types/UnitOfMeasure.hpp"
#include "../types/TradingReferencePriceEx.hpp"
#include "../bitfields/SettlPriceType.hpp"
#include "../types/OpenInterestQty.hpp"
#include "../types/ClearedVolume.hpp"
#include "../types/HighLimitPriceEx.hpp"
#include "../types/LowLimitPriceEx.hpp"
#include "../types/MaxPriceVariationEx.hpp"
#include "../types/MainFraction.hpp"
#include "../types/SubFraction.hpp"
#include "../types/TradingReferenceDate.hpp"
#include "../structs/MessageHeader.hpp"

namespace cme::mdp3::v9 {

#pragma pack(push, 1)

// MDInstrumentDefinitionSpread
struct MdInstrumentDefinitionSpread {

    MatchEventIndicator match_event_indicator;
    TotNumReportsOptional tot_num_reports_optional;
    SecurityUpdateAction security_update_action;
    LastUpdateTime last_update_time;
    MdSecurityTradingStatus md_security_trading_status;
    ApplId appl_id;
    MarketSegmentId market_segment_id;
    UnderlyingProductOptional underlying_product_optional;
    SecurityExchange security_exchange;
    SecurityGroup security_group;
    Asset asset;
    Symbol symbol;
    SecurityId security_id;
    SecurityType security_type;
    CfiCode cfi_code;
    MaturityMonthYear maturity_month_year;
    Currency currency;
    SecuritySubType security_sub_type;
    UserDefinedInstrument user_defined_instrument;
    MatchAlgorithm match_algorithm;
    MinTradeVol min_trade_vol;
    MaxTradeVol max_trade_vol;
    MinPriceIncrementOptionalEx min_price_increment_optional_ex;
    DisplayFactorEx display_factor_ex;
    PriceDisplayFormat price_display_format;
    PriceRatioEx price_ratio_ex;
    TickRule tick_rule;
    UnitOfMeasure unit_of_measure;
    TradingReferencePriceEx trading_reference_price_ex;
    SettlPriceType settl_price_type;
    OpenInterestQty open_interest_qty;
    ClearedVolume cleared_volume;
    HighLimitPriceEx high_limit_price_ex;
    LowLimitPriceEx low_limit_price_ex;
    MaxPriceVariationEx max_price_variation_ex;
    MainFraction main_fraction;
    SubFraction sub_fraction;
    TradingReferenceDate trading_reference_date;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint16_t message_type = 56;

    // parse method
    static MdInstrumentDefinitionSpread* parse(std::byte* buffer) {
        return reinterpret_cast<MdInstrumentDefinitionSpread*>(buffer);
    }

    // parse method const
    static const MdInstrumentDefinitionSpread* parse(const std::byte* buffer) {
        return reinterpret_cast<const MdInstrumentDefinitionSpread*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const MdInstrumentDefinitionSpread* parse(const MessageHeader* header) {
        return reinterpret_cast<const MdInstrumentDefinitionSpread*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
