#pragma once

#include "../types/TsRecv.hpp"
#include "../types/MinPriceIncrement.hpp"
#include "../types/DisplayFactor.hpp"
#include "../types/Expiration.hpp"
#include "../types/Activation.hpp"
#include "../types/HighLimitPrice.hpp"
#include "../types/LowLimitPrice.hpp"
#include "../types/MaxPriceVariation.hpp"
#include "../types/UnitOfMeasureQty.hpp"
#include "../types/MinPriceIncrementAmount.hpp"
#include "../types/PriceRatio.hpp"
#include "../types/StrikePrice.hpp"
#include "../types/RawInstrumentId.hpp"
#include "../types/LegPrice.hpp"
#include "../types/LegDelta.hpp"
#include "../types/InstAttribValue.hpp"
#include "../types/UnderlyingId.hpp"
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
#include "../types/LegInstrumentId.hpp"
#include "../types/LegRatioPriceNumerator.hpp"
#include "../types/LegRatioPriceDenominator.hpp"
#include "../types/LegRatioQtyNumerator.hpp"
#include "../types/LegRatioQtyDenominator.hpp"
#include "../types/LegUnderlyingId.hpp"
#include "../types/ApplId.hpp"
#include "../types/MaturityYear.hpp"
#include "../types/DecayStartDate.hpp"
#include "../types/Channel.hpp"
#include "../types/LegCount.hpp"
#include "../types/LegIndex.hpp"
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
#include "../types/LegRawSymbol.hpp"
#include "../types/InstrumentClass.hpp"
#include "../types/MatchAlgorithm.hpp"
#include "../types/MainFraction.hpp"
#include "../types/PriceDisplayFormat.hpp"
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
#include "../types/LegInstrumentClass.hpp"
#include "../types/LegSide.hpp"
#include "../types/Reserved17.hpp"

namespace databento::marketdata::normalized::dbn::v3 {

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
    UnitOfMeasureQty unit_of_measure_qty;
    MinPriceIncrementAmount min_price_increment_amount;
    PriceRatio price_ratio;
    StrikePrice strike_price;
    RawInstrumentId raw_instrument_id;
    LegPrice leg_price;
    LegDelta leg_delta;
    InstAttribValue inst_attrib_value;
    UnderlyingId underlying_id;
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
    LegInstrumentId leg_instrument_id;
    LegRatioPriceNumerator leg_ratio_price_numerator;
    LegRatioPriceDenominator leg_ratio_price_denominator;
    LegRatioQtyNumerator leg_ratio_qty_numerator;
    LegRatioQtyDenominator leg_ratio_qty_denominator;
    LegUnderlyingId leg_underlying_id;
    ApplId appl_id;
    MaturityYear maturity_year;
    DecayStartDate decay_start_date;
    Channel channel;
    LegCount leg_count;
    LegIndex leg_index;
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
    LegRawSymbol leg_raw_symbol;
    InstrumentClass instrument_class;
    MatchAlgorithm match_algorithm;
    MainFraction main_fraction;
    PriceDisplayFormat price_display_format;
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
    LegInstrumentClass leg_instrument_class;
    LegSide leg_side;
    Reserved17 reserved_17;

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
