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
#include "../structs/CorrectedPriorDayTradeDateAndTime.hpp"
#include "../types/TradeReportingFacilityId.hpp"
#include "../types/OriginalSaleCondition.hpp"
#include "../types/OriginalTradePrice.hpp"
#include "../types/OriginalTradeVolume.hpp"
#include "../types/OriginalSellersSaleDays.hpp"
#include "../types/OriginalStopStockIndicator.hpp"
#include "../types/OriginalTradeThroughExemptIndicator.hpp"
#include "../types/OriginalShortSaleRestrictionIndicator.hpp"
#include "../structs/OriginalPriorDayTradeDateAndTime.hpp"

namespace siac::cts::output::cta::v2_11_b {

#pragma pack(push, 1)

// Used to correct a transaction originally reported on a trading day earlier than the current trading day. To be descoped when Fractional Trade Volume publication is activated
struct PriorDayTradeCorrectionMessage {

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
    CorrectedPriorDayTradeDateAndTime corrected_prior_day_trade_date_and_time;
    TradeReportingFacilityId trade_reporting_facility_id;
    OriginalSaleCondition original_sale_condition;
    OriginalTradePrice original_trade_price;
    OriginalTradeVolume original_trade_volume;
    OriginalSellersSaleDays original_sellers_sale_days;
    OriginalStopStockIndicator original_stop_stock_indicator;
    OriginalTradeThroughExemptIndicator original_trade_through_exempt_indicator;
    OriginalShortSaleRestrictionIndicator original_short_sale_restriction_indicator;
    OriginalPriorDayTradeDateAndTime original_prior_day_trade_date_and_time;

    // parse method
    static PriorDayTradeCorrectionMessage* parse(std::byte* buffer) {
        return reinterpret_cast<PriorDayTradeCorrectionMessage*>(buffer);
    }

    // parse method const
    static const PriorDayTradeCorrectionMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const PriorDayTradeCorrectionMessage*>(buffer);
    }
};

#pragma pack(pop)
}
