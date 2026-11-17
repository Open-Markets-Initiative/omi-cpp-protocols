// Databento.MarketData.Normalized.Dbn.v2: messages/InstrumentDefMsg.hpp
#pragma once

#include "../types/TsRecv.hpp"
#include "../types/MinPriceIncrement.hpp"
#include "../types/DisplayFactor.hpp"
#include "../types/Expiration.hpp"
#include "../types/Activation.hpp"
#include "../types/HighLimitPrice.hpp"
#include "../types/LowLimitPrice.hpp"
#include "../types/MaxPriceVariation.hpp"
#include "../types/TradingReferencePrice.hpp"
#include "../types/UnitOfMeasureQty.hpp"
#include "../types/MinPriceIncrementAmount.hpp"
#include "../types/PriceRatio.hpp"
#include "../types/StrikePrice.hpp"
#include "../types/InstAttribValue.hpp"
#include "../types/UnderlyingId.hpp"
#include "../types/RawInstrumentId.hpp"
#include "../types/MarketDepthImplied.hpp"
#include "../types/MarketDepth.hpp"
#include "../types/MarketSegmentId.hpp"
#include "../types/MaxTradeVol.hpp"
#include "../types/MinLotSize.hpp"
#include "../types/MinLotSizeBlock.hpp"
#include "../types/MinLotSizeRoundLot.hpp"
#include "../types/MinTradeVol.hpp"
#include "../types/ContractMultiplier.hpp"
#include "../types/DecayQuantity.hpp"
#include "../types/OriginalContractSize.hpp"
#include "../types/TradingReferenceDate.hpp"
#include "../types/ApplId.hpp"
#include "../types/MaturityYear.hpp"
#include "../types/DecayStartDate.hpp"
#include "../types/Channel.hpp"
#include "../types/Currency.hpp"
#include "../types/SettlCurrency.hpp"
#include "../types/Secsubtype.hpp"
#include "../types/RawSymbol.hpp"
#include "../types/Group.hpp"
#include "../types/Exchange.hpp"
#include "../types/Asset.hpp"
#include "../types/Cfi.hpp"
#include "../types/SecurityType.hpp"
#include "../types/UnitOfMeasure.hpp"
#include "../types/Underlying.hpp"
#include "../types/StrikePriceCurrency.hpp"
#include "../types/InstrumentClass.hpp"
#include "../types/MatchAlgorithm.hpp"
#include "../types/MdSecurityTradingStatus.hpp"
#include "../types/MainFraction.hpp"
#include "../types/PriceDisplayFormat.hpp"
#include "../types/SettlPriceType.hpp"
#include "../types/SubFraction.hpp"
#include "../types/UnderlyingProduct.hpp"
#include "../types/SecurityUpdateAction.hpp"
#include "../types/MaturityMonth.hpp"
#include "../types/MaturityDay.hpp"
#include "../types/MaturityWeek.hpp"
#include "../types/UserDefinedInstrument.hpp"
#include "../types/ContractMultiplierUnit.hpp"
#include "../types/FlowScheduleType.hpp"
#include "../types/TickRule.hpp"
#include "../types/Reserved10.hpp"

namespace databento::marketdata::normalized::dbn::v2 {

#pragma pack(push, 1)

// A definition of an instrument; the record of the definition schema
struct InstrumentDefMsg {

    TsRecv ts_recv;
    MinPriceIncrement min_price_increment;
    DisplayFactor display_factor;
    Expiration expiration;
    Activation activation;
    HighLimitPrice high_limit_price;
    LowLimitPrice low_limit_price;
    MaxPriceVariation max_price_variation;
    TradingReferencePrice trading_reference_price;
    UnitOfMeasureQty unit_of_measure_qty;
    MinPriceIncrementAmount min_price_increment_amount;
    PriceRatio price_ratio;
    StrikePrice strike_price;
    InstAttribValue inst_attrib_value;
    UnderlyingId underlying_id;
    RawInstrumentId raw_instrument_id;
    MarketDepthImplied market_depth_implied;
    MarketDepth market_depth;
    MarketSegmentId market_segment_id;
    MaxTradeVol max_trade_vol;
    MinLotSize min_lot_size;
    MinLotSizeBlock min_lot_size_block;
    MinLotSizeRoundLot min_lot_size_round_lot;
    MinTradeVol min_trade_vol;
    ContractMultiplier contract_multiplier;
    DecayQuantity decay_quantity;
    OriginalContractSize original_contract_size;
    TradingReferenceDate trading_reference_date;
    ApplId appl_id;
    MaturityYear maturity_year;
    DecayStartDate decay_start_date;
    Channel channel;
    Currency currency;
    SettlCurrency settl_currency;
    Secsubtype secsubtype;
    RawSymbol raw_symbol;
    Group group;
    Exchange exchange;
    Asset asset;
    Cfi cfi;
    SecurityType security_type;
    UnitOfMeasure unit_of_measure;
    Underlying underlying;
    StrikePriceCurrency strike_price_currency;
    InstrumentClass instrument_class;
    MatchAlgorithm match_algorithm;
    MdSecurityTradingStatus md_security_trading_status;
    MainFraction main_fraction;
    PriceDisplayFormat price_display_format;
    SettlPriceType settl_price_type;
    SubFraction sub_fraction;
    UnderlyingProduct underlying_product;
    SecurityUpdateAction security_update_action;
    MaturityMonth maturity_month;
    MaturityDay maturity_day;
    MaturityWeek maturity_week;
    UserDefinedInstrument user_defined_instrument;
    ContractMultiplierUnit contract_multiplier_unit;
    FlowScheduleType flow_schedule_type;
    TickRule tick_rule;
    Reserved10 reserved_10;

    // parse method
    static InstrumentDefMsg* parse(std::byte* buffer) {
        return reinterpret_cast<InstrumentDefMsg*>(buffer);
    }

    // parse method const
    static const InstrumentDefMsg* parse(const std::byte* buffer) {
        return reinterpret_cast<const InstrumentDefMsg*>(buffer);
    }
};

#pragma pack(pop)
}
