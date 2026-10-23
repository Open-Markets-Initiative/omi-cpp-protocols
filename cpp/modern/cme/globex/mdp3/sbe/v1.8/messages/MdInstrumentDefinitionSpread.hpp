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
#include "../types/MinPriceIncrement.hpp"
#include "../types/DisplayFactor.hpp"
#include "../types/PriceDisplayFormat.hpp"
#include "../types/PriceRatio.hpp"
#include "../types/TickRule.hpp"
#include "../types/UnitOfMeasure.hpp"
#include "../types/TradingReferencePrice.hpp"
#include "../bitfields/SettlPriceType.hpp"
#include "../types/OpenInterestQty.hpp"
#include "../types/ClearedVolume.hpp"
#include "../types/HighLimitPrice.hpp"
#include "../types/LowLimitPrice.hpp"
#include "../types/MaxPriceVariation.hpp"
#include "../types/MainFraction.hpp"
#include "../types/SubFraction.hpp"
#include "../types/TradingReferenceDate.hpp"
#include "../structs/MessageHeader.hpp"

namespace cme::mdp3::v8 {

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
    MinPriceIncrement min_price_increment;
    DisplayFactor display_factor;
    PriceDisplayFormat price_display_format;
    PriceRatio price_ratio;
    TickRule tick_rule;
    UnitOfMeasure unit_of_measure;
    TradingReferencePrice trading_reference_price;
    SettlPriceType settl_price_type;
    OpenInterestQty open_interest_qty;
    ClearedVolume cleared_volume;
    HighLimitPrice high_limit_price;
    LowLimitPrice low_limit_price;
    MaxPriceVariation max_price_variation;
    MainFraction main_fraction;
    SubFraction sub_fraction;
    TradingReferenceDate trading_reference_date;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint16_t message_type = 29;

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
