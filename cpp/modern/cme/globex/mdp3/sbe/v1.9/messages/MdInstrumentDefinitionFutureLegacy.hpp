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
#include "../structs/MaturityMonthYear.hpp"
#include "../types/Currency.hpp"
#include "../types/SettlCurrency.hpp"
#include "../types/MatchAlgorithm.hpp"
#include "../types/MinTradeVol.hpp"
#include "../types/MaxTradeVol.hpp"
#include "../types/MinPriceIncrement.hpp"
#include "../types/DisplayFactor.hpp"
#include "../types/MainFraction.hpp"
#include "../types/SubFraction.hpp"
#include "../types/PriceDisplayFormat.hpp"
#include "../types/UnitOfMeasure.hpp"
#include "../types/UnitOfMeasureQty.hpp"
#include "../types/TradingReferencePrice.hpp"
#include "../bitfields/SettlPriceType.hpp"
#include "../types/OpenInterestQty.hpp"
#include "../types/ClearedVolume.hpp"
#include "../types/HighLimitPrice.hpp"
#include "../types/LowLimitPrice.hpp"
#include "../types/MaxPriceVariation.hpp"
#include "../types/DecayQuantity.hpp"
#include "../types/DecayStartDate.hpp"
#include "../types/OriginalContractSize.hpp"
#include "../types/ContractMultiplier.hpp"
#include "../types/ContractMultiplierUnit.hpp"
#include "../types/FlowScheduleType.hpp"
#include "../types/MinPriceIncrementAmount.hpp"
#include "../types/UserDefinedInstrument.hpp"
#include "../types/TradingReferenceDate.hpp"
#include "../structs/MessageHeader.hpp"

namespace cme::mdp3::v9 {

#pragma pack(push, 1)

// MDInstrumentDefinitionFuture
struct MdInstrumentDefinitionFutureLegacy {

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
    MaturityMonthYear maturity_month_year;
    Currency currency;
    SettlCurrency settl_currency;
    MatchAlgorithm match_algorithm;
    MinTradeVol min_trade_vol;
    MaxTradeVol max_trade_vol;
    MinPriceIncrement min_price_increment;
    DisplayFactor display_factor;
    MainFraction main_fraction;
    SubFraction sub_fraction;
    PriceDisplayFormat price_display_format;
    UnitOfMeasure unit_of_measure;
    UnitOfMeasureQty unit_of_measure_qty;
    TradingReferencePrice trading_reference_price;
    SettlPriceType settl_price_type;
    OpenInterestQty open_interest_qty;
    ClearedVolume cleared_volume;
    HighLimitPrice high_limit_price;
    LowLimitPrice low_limit_price;
    MaxPriceVariation max_price_variation;
    DecayQuantity decay_quantity;
    DecayStartDate decay_start_date;
    OriginalContractSize original_contract_size;
    ContractMultiplier contract_multiplier;
    ContractMultiplierUnit contract_multiplier_unit;
    FlowScheduleType flow_schedule_type;
    MinPriceIncrementAmount min_price_increment_amount;
    UserDefinedInstrument user_defined_instrument;
    TradingReferenceDate trading_reference_date;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint16_t message_type = 27;

    // parse method
    static MdInstrumentDefinitionFutureLegacy* parse(std::byte* buffer) {
        return reinterpret_cast<MdInstrumentDefinitionFutureLegacy*>(buffer);
    }

    // parse method const
    static const MdInstrumentDefinitionFutureLegacy* parse(const std::byte* buffer) {
        return reinterpret_cast<const MdInstrumentDefinitionFutureLegacy*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const MdInstrumentDefinitionFutureLegacy* parse(const MessageHeader* header) {
        return reinterpret_cast<const MdInstrumentDefinitionFutureLegacy*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
