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
#include "../types/MinPriceIncrementEx.hpp"
#include "../types/DisplayFactor.hpp"
#include "../types/UnitOfMeasure.hpp"
#include "../types/UnitOfMeasureQty.hpp"
#include "../types/TradingReferencePrice.hpp"
#include "../types/TradingReferenceDate.hpp"
#include "../types/HighLimitPrice.hpp"
#include "../types/LowLimitPrice.hpp"
#include "../types/MaxPriceVariation.hpp"
#include "../types/FinancialInstrumentFullName.hpp"
#include "../types/PartyRoleClearingOrg.hpp"
#include "../types/StartDate.hpp"
#include "../types/EndDate.hpp"
#include "../types/TerminationType.hpp"
#include "../types/RepoSubType.hpp"
#include "../types/MoneyOrPar.hpp"
#include "../types/MaxNoOfSubstitutions.hpp"
#include "../types/PriceQuoteMethod.hpp"
#include "../types/UserDefinedInstrument.hpp"
#include "../types/RiskSet.hpp"
#include "../types/MarketSet.hpp"
#include "../types/InstrumentGuid.hpp"
#include "../types/TermCode.hpp"
#include "../types/BrokenDateTermType.hpp"
#include "../structs/SimpleBinaryHeader.hpp"

namespace cme::mdp3::v13 {

#pragma pack(push, 1)

// MDInstrumentDefinitionRepo
struct MdInstrumentDefinitionRepo {

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
    MinPriceIncrementEx min_price_increment_ex;
    DisplayFactor display_factor;
    UnitOfMeasure unit_of_measure;
    UnitOfMeasureQty unit_of_measure_qty;
    TradingReferencePrice trading_reference_price;
    TradingReferenceDate trading_reference_date;
    HighLimitPrice high_limit_price;
    LowLimitPrice low_limit_price;
    MaxPriceVariation max_price_variation;
    FinancialInstrumentFullName financial_instrument_full_name;
    PartyRoleClearingOrg party_role_clearing_org;
    StartDate start_date;
    EndDate end_date;
    TerminationType termination_type;
    RepoSubType repo_sub_type;
    MoneyOrPar money_or_par;
    MaxNoOfSubstitutions max_no_of_substitutions;
    PriceQuoteMethod price_quote_method;
    UserDefinedInstrument user_defined_instrument;
    RiskSet risk_set;
    MarketSet market_set;
    InstrumentGuid instrument_guid;
    TermCode term_code;
    BrokenDateTermType broken_date_term_type;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint16_t message_type = 58;

    // parse method
    static MdInstrumentDefinitionRepo* parse(std::byte* buffer) {
        return reinterpret_cast<MdInstrumentDefinitionRepo*>(buffer);
    }

    // parse method const
    static const MdInstrumentDefinitionRepo* parse(const std::byte* buffer) {
        return reinterpret_cast<const MdInstrumentDefinitionRepo*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const MdInstrumentDefinitionRepo* parse(const SimpleBinaryHeader* header) {
        return reinterpret_cast<const MdInstrumentDefinitionRepo*>(reinterpret_cast<const std::byte*>(header) + sizeof(SimpleBinaryHeader));
    }
};

#pragma pack(pop)
}
