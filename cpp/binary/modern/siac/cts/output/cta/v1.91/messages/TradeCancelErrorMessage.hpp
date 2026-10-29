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
#include "../types/TradeReportingFacilityId.hpp"
#include "../types/OriginalParticipantReferenceNumber.hpp"
#include "../structs/Timestamp2.hpp"
#include "../types/CancelErrorAction.hpp"
#include "../types/ShortSaleRestrictionIndicator.hpp"
#include "../types/PrimaryListingMarketParticipantId.hpp"
#include "../types/FinancialStatusIndicator.hpp"
#include "../structs/ConsolidatedData.hpp"
#include "../structs/ParticipantData.hpp"

namespace siac::cts::output::cta::v1_91 {

#pragma pack(push, 1)

// The Trade Cancel/Error message is used cancel or error Cta eligible securities, Local Issues or Bond information.
struct TradeCancelErrorMessage {

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
    TradeReportingFacilityId trade_reporting_facility_id;
    OriginalParticipantReferenceNumber original_participant_reference_number;
    Timestamp2 timestamp_2;
    CancelErrorAction cancel_error_action;
    ShortSaleRestrictionIndicator short_sale_restriction_indicator;
    PrimaryListingMarketParticipantId primary_listing_market_participant_id;
    FinancialStatusIndicator financial_status_indicator;
    ConsolidatedData consolidated_data;
    ParticipantData participant_data;

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
