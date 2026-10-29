#pragma once

#include "../types/ParticipantId.hpp"
#include "../structs/Timestamp1.hpp"
#include "../types/MessageId.hpp"
#include "../types/TransactionId.hpp"
#include "../types/ParticipantReferenceNumber.hpp"
#include "../types/SecuritySymbol.hpp"
#include "../types/InstrumentType.hpp"
#include "../structs/SaleConditions.hpp"
#include "../types/TradePrice.hpp"
#include "../types/TradeVolume.hpp"
#include "../types/SellersSaleDays.hpp"
#include "../types/StopStockIndicator.hpp"
#include "../types/TradeThroughExemptIndicator.hpp"
#include "../types/ShortSaleRestrictionIndicator.hpp"
#include "../types/TradeReportingFacilityId.hpp"
#include "../structs/PriorDayTradeDateAndTime.hpp"

namespace siac::cts::output::cta::v1_91 {

#pragma pack(push, 1)

// The Prior Day Trade message is used to report a Cta Equity, Local Issue or Bond transaction which occurred earlier than the current trading day and was not reported.
struct PriorDayTradeMessage {

    ParticipantId participant_id;
    Timestamp1 timestamp_1;
    MessageId message_id;
    TransactionId transaction_id;
    ParticipantReferenceNumber participant_reference_number;
    SecuritySymbol security_symbol;
    InstrumentType instrument_type;
    SaleConditions sale_conditions;
    TradePrice trade_price;
    TradeVolume trade_volume;
    SellersSaleDays sellers_sale_days;
    StopStockIndicator stop_stock_indicator;
    TradeThroughExemptIndicator trade_through_exempt_indicator;
    ShortSaleRestrictionIndicator short_sale_restriction_indicator;
    TradeReportingFacilityId trade_reporting_facility_id;
    PriorDayTradeDateAndTime prior_day_trade_date_and_time;

    // parse method
    static PriorDayTradeMessage* parse(std::byte* buffer) {
        return reinterpret_cast<PriorDayTradeMessage*>(buffer);
    }

    // parse method const
    static const PriorDayTradeMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const PriorDayTradeMessage*>(buffer);
    }
};

#pragma pack(pop)
}
