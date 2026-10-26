#pragma once

#include "../types/ParticipantId.hpp"
#include "../structs/Timestamp1.hpp"
#include "../types/MessageId.hpp"
#include "../types/TransactionId.hpp"
#include "../types/ParticipantReferenceNumber.hpp"
#include "../types/SecuritySymbol.hpp"
#include "../types/InstrumentType.hpp"
#include "../structs/SaleCondition4.hpp"
#include "../types/TradePrice.hpp"
#include "../types/TradeVolume.hpp"
#include "../types/SellersSaleDays.hpp"
#include "../types/StopStockIndicator.hpp"
#include "../types/TradeThroughExemptIndicator.hpp"
#include "../types/TradeReportingFacilityId.hpp"
#include "../types/OriginalParticipantReferenceNumber.hpp"
#include "../structs/Timestamp2.hpp"
#include "../types/CancelErrorAction.hpp"
#include "../types/ShortSaleRestrictionIndicator.hpp"
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

// Used to cancel or error CTA eligible securities, Local Issues or Bond information. To be descoped when Fractional Trade Volume publication is activated
struct TradeCancelErrorMessage {

    ParticipantId participant_id;
    Timestamp1 timestamp_1;
    MessageId message_id;
    TransactionId transaction_id;
    ParticipantReferenceNumber participant_reference_number;
    SecuritySymbol security_symbol;
    InstrumentType instrument_type;
    SaleCondition4 sale_condition_4;
    TradePrice trade_price;
    TradeVolume trade_volume;
    SellersSaleDays sellers_sale_days;
    StopStockIndicator stop_stock_indicator;
    TradeThroughExemptIndicator trade_through_exempt_indicator;
    TradeReportingFacilityId trade_reporting_facility_id;
    OriginalParticipantReferenceNumber original_participant_reference_number;
    Timestamp2 timestamp_2;
    CancelErrorAction cancel_error_action;
    ShortSaleRestrictionIndicator short_sale_restriction_indicator;
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
    static TradeCancelErrorMessage* parse(std::byte* buffer) {
        return reinterpret_cast<TradeCancelErrorMessage*>(buffer);
    }

    // parse method const
    static const TradeCancelErrorMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const TradeCancelErrorMessage*>(buffer);
    }
};

#pragma pack(pop)
}
