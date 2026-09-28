#pragma once

#include "../types/SecurityId.hpp"
#include "../types/SecurityExchange.hpp"
#include "../types/SecurityIdSource.hpp"
#include "../types/SecurityGroup.hpp"
#include "../types/Symbol.hpp"
#include "../types/SecurityUpdateAction.hpp"
#include "../types/SecurityType.hpp"
#include "../types/SecuritySubType.hpp"
#include "../types/TotNoRelatedSym.hpp"
#include "../types/MinPriceIncrementLegacy.hpp"
#include "../types/StrikePrice.hpp"
#include "../types/ContractMultiplier.hpp"
#include "../types/PriceDivisor.hpp"
#include "../types/SecurityValidityTimestamp.hpp"
#include "../types/NoSharesIssued.hpp"
#include "../types/ClearingHouseId.hpp"
#include "../types/MinOrderQty.hpp"
#include "../types/MaxOrderQty.hpp"
#include "../types/MinLotSize.hpp"
#include "../types/MinTradeVol.hpp"
#include "../types/CorporateActionEventId.hpp"
#include "../types/IssueDate.hpp"
#include "../types/MaturityDate.hpp"
#include "../types/CountryOfIssue.hpp"
#include "../types/StartDate.hpp"
#include "../types/EndDate.hpp"
#include "../types/SettlType.hpp"
#include "../types/SettlDate.hpp"
#include "../types/DatedDate.hpp"
#include "../types/IsinNumber.hpp"
#include "../types/Asset.hpp"
#include "../types/CfiCode.hpp"
#include "../structs/MaturityMonthYear.hpp"
#include "../structs/ContractSettlMonth.hpp"
#include "../types/Currency.hpp"
#include "../types/StrikeCurrency.hpp"
#include "../types/SettlCurrency.hpp"
#include "../types/SecurityStrategyType.hpp"
#include "../types/LotType.hpp"
#include "../types/TickSizeDenominator.hpp"
#include "../types/Product.hpp"
#include "../types/ExerciseStyle.hpp"
#include "../types/PutOrCall.hpp"
#include "../types/PriceTypeOptional.hpp"
#include "../types/MarketSegmentId.hpp"
#include "../types/GovernanceIndicator.hpp"
#include "../types/SecurityMatchType.hpp"
#include "../types/LastFragment.hpp"
#include "../types/MultiLegModel.hpp"
#include "../types/MultiLegPriceMethod.hpp"
#include "../types/MinCrossQty.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v1_8 {

#pragma pack(push, 1)

// SecurityDefinition_4Message
struct DeprecatedSecurityDefinitionMessage {

    SecurityId security_id;
    SecurityExchange security_exchange;
    SecurityIdSource security_id_source;
    SecurityGroup security_group;
    Symbol symbol;
    SecurityUpdateAction security_update_action;
    SecurityType security_type;
    SecuritySubType security_sub_type;
    TotNoRelatedSym tot_no_related_sym;
    MinPriceIncrementLegacy min_price_increment_legacy;
    StrikePrice strike_price;
    ContractMultiplier contract_multiplier;
    PriceDivisor price_divisor;
    SecurityValidityTimestamp security_validity_timestamp;
    NoSharesIssued no_shares_issued;
    ClearingHouseId clearing_house_id;
    MinOrderQty min_order_qty;
    MaxOrderQty max_order_qty;
    MinLotSize min_lot_size;
    MinTradeVol min_trade_vol;
    CorporateActionEventId corporate_action_event_id;
    IssueDate issue_date;
    MaturityDate maturity_date;
    CountryOfIssue country_of_issue;
    StartDate start_date;
    EndDate end_date;
    SettlType settl_type;
    SettlDate settl_date;
    DatedDate dated_date;
    IsinNumber isin_number;
    Asset asset;
    CfiCode cfi_code;
    MaturityMonthYear maturity_month_year;
    ContractSettlMonth contract_settl_month;
    Currency currency;
    StrikeCurrency strike_currency;
    SettlCurrency settl_currency;
    SecurityStrategyType security_strategy_type;
    LotType lot_type;
    TickSizeDenominator tick_size_denominator;
    Product product;
    ExerciseStyle exercise_style;
    PutOrCall put_or_call;
    PriceTypeOptional price_type_optional;
    MarketSegmentId market_segment_id;
    GovernanceIndicator governance_indicator;
    SecurityMatchType security_match_type;
    LastFragment last_fragment;
    MultiLegModel multi_leg_model;
    MultiLegPriceMethod multi_leg_price_method;
    MinCrossQty min_cross_qty;

    // parse method
    static DeprecatedSecurityDefinitionMessage* parse(std::byte* buffer) {
        return reinterpret_cast<DeprecatedSecurityDefinitionMessage*>(buffer);
    }

    // parse method const
    static const DeprecatedSecurityDefinitionMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const DeprecatedSecurityDefinitionMessage*>(buffer);
    }
};

#pragma pack(pop)
}
