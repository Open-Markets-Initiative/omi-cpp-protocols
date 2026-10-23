#pragma once

#include "../types/ParticipantId.hpp"
#include "../structs/Timestamp1.hpp"
#include "../types/MessageId.hpp"
#include "../types/TransactionId.hpp"
#include "../types/ParticipantReferenceNumber.hpp"
#include "../types/SecuritySymbol.hpp"
#include "../types/InstrumentType.hpp"
#include "../types/CorrectedSaleCondition.hpp"
#include "../types/CorrectedTradePrice.hpp"
#include "../types/CorrectedTradeVolume.hpp"
#include "../types/CorrectedSellersSaleDays.hpp"
#include "../types/CorrectedStopStockIndicator.hpp"
#include "../types/CorrectedTradeThroughExemptIndicator.hpp"
#include "../types/CorrectedShortSaleRestrictionIndicator.hpp"
#include "../types/TradeReportingFacilityId.hpp"
#include "../structs/Timestamp2.hpp"
#include "../types/OriginalParticipantReferenceNumber.hpp"
#include "../types/OriginalSaleCondition.hpp"
#include "../types/OriginalTradePrice.hpp"
#include "../types/OriginalTradeVolume.hpp"
#include "../types/OriginalSellersSaleDays.hpp"
#include "../types/OriginalStopStockIndicator.hpp"
#include "../types/OriginalTradeThroughExemptIndicator.hpp"
#include "../types/OriginalShortSaleRestrictionIndicator.hpp"
#include "../types/PrimaryListingMarketParticipantId.hpp"
#include "../types/FinancialStatusIndicator.hpp"
#include "../types/ConsolidatedPreviousClosePriceDate.hpp"
#include "../types/ConsolidatedLastParticipantId.hpp"
#include "../types/ConsolidatedLastPrice.hpp"
#include "../types/ConsolidatedHighPrice.hpp"
#include "../types/ConsolidatedLowPrice.hpp"
#include "../types/ConsolidatedTotalVolume.hpp"
#include "../types/ConsolidatedTick.hpp"
#include "../types/ParticipantPreviousClosePriceDate.hpp"
#include "../types/ParticipantLastPrice.hpp"
#include "../types/ParticipantHighPrice.hpp"
#include "../types/ParticipantLowPrice.hpp"
#include "../types/ParticipantOpenPrice.hpp"
#include "../types/ParticipantTotalVolume.hpp"
#include "../types/ParticipantTick.hpp"

namespace siac::cts::output::cta::v2_11_b {

#pragma pack(push, 1)

// Used to correct CTA eligible Equity, Local Issue or Bond information. To be descoped when Fractional Trade Volume publication is activated
struct TradeCorrectionMessage {

    ParticipantId participant_id;
    Timestamp1 timestamp_1;
    MessageId message_id;
    TransactionId transaction_id;
    ParticipantReferenceNumber participant_reference_number;
    SecuritySymbol security_symbol;
    InstrumentType instrument_type;
    CorrectedSaleCondition corrected_sale_condition;
    CorrectedTradePrice corrected_trade_price;
    CorrectedTradeVolume corrected_trade_volume;
    CorrectedSellersSaleDays corrected_sellers_sale_days;
    CorrectedStopStockIndicator corrected_stop_stock_indicator;
    CorrectedTradeThroughExemptIndicator corrected_trade_through_exempt_indicator;
    CorrectedShortSaleRestrictionIndicator corrected_short_sale_restriction_indicator;
    TradeReportingFacilityId trade_reporting_facility_id;
    Timestamp2 timestamp_2;
    OriginalParticipantReferenceNumber original_participant_reference_number;
    OriginalSaleCondition original_sale_condition;
    OriginalTradePrice original_trade_price;
    OriginalTradeVolume original_trade_volume;
    OriginalSellersSaleDays original_sellers_sale_days;
    OriginalStopStockIndicator original_stop_stock_indicator;
    OriginalTradeThroughExemptIndicator original_trade_through_exempt_indicator;
    OriginalShortSaleRestrictionIndicator original_short_sale_restriction_indicator;
    PrimaryListingMarketParticipantId primary_listing_market_participant_id;
    FinancialStatusIndicator financial_status_indicator;
    ConsolidatedPreviousClosePriceDate consolidated_previous_close_price_date;
    ConsolidatedLastParticipantId consolidated_last_participant_id;
    ConsolidatedLastPrice consolidated_last_price;
    ConsolidatedHighPrice consolidated_high_price;
    ConsolidatedLowPrice consolidated_low_price;
    ConsolidatedTotalVolume consolidated_total_volume;
    ConsolidatedTick consolidated_tick;
    ParticipantPreviousClosePriceDate participant_previous_close_price_date;
    ParticipantLastPrice participant_last_price;
    ParticipantHighPrice participant_high_price;
    ParticipantLowPrice participant_low_price;
    ParticipantOpenPrice participant_open_price;
    ParticipantTotalVolume participant_total_volume;
    ParticipantTick participant_tick;

    // parse method
    static TradeCorrectionMessage* parse(std::byte* buffer) {
        return reinterpret_cast<TradeCorrectionMessage*>(buffer);
    }

    // parse method const
    static const TradeCorrectionMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const TradeCorrectionMessage*>(buffer);
    }
};

#pragma pack(pop)
}
