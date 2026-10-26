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
#include "../types/ShortSaleRestrictionIndicator.hpp"
#include "../types/TradeReportingFacilityId.hpp"
#include "../structs/PriorDayTradeDateAndTime.hpp"
#include "../types/CancelErrorAction.hpp"

namespace siac::cts::output::cta::v2_11_b {

#pragma pack(push, 1)

// Used to report the cancellation of a trade or error a trade that never took place but was reported, for transactions originally reported earlier than the current day. To be descoped when Fractional Trade Volume publication is activated
struct PriorDayTradeCancelErrorMessage {

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
    ShortSaleRestrictionIndicator short_sale_restriction_indicator;
    TradeReportingFacilityId trade_reporting_facility_id;
    PriorDayTradeDateAndTime prior_day_trade_date_and_time;
    CancelErrorAction cancel_error_action;

    // parse method
    static PriorDayTradeCancelErrorMessage* parse(std::byte* buffer) {
        return reinterpret_cast<PriorDayTradeCancelErrorMessage*>(buffer);
    }

    // parse method const
    static const PriorDayTradeCancelErrorMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const PriorDayTradeCancelErrorMessage*>(buffer);
    }
};

#pragma pack(pop)
}
