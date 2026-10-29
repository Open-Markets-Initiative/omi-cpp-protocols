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
#include "../structs/Timestamp2.hpp"
#include "../types/ShortSaleRestrictionIndicator.hpp"
#include "../types/PrimaryListingMarketParticipantId.hpp"
#include "../types/FinancialStatusIndicator.hpp"
#include "../types/HeldTradeIndicator.hpp"
#include "../types/ConsolidatedHighLowLastIndicator.hpp"
#include "../types/ParticipantOpenHighLowLastIndicator.hpp"

namespace siac::cts::output::cta::v1_91 {

#pragma pack(push, 1)

// The Long Trade message is used to report trade information for Cta eligible Equity, Local Issue or Bonds.
struct LongTradeMessage {

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
    Timestamp2 timestamp_2;
    ShortSaleRestrictionIndicator short_sale_restriction_indicator;
    PrimaryListingMarketParticipantId primary_listing_market_participant_id;
    FinancialStatusIndicator financial_status_indicator;
    HeldTradeIndicator held_trade_indicator;
    ConsolidatedHighLowLastIndicator consolidated_high_low_last_indicator;
    ParticipantOpenHighLowLastIndicator participant_open_high_low_last_indicator;

    // parse method
    static LongTradeMessage* parse(std::byte* buffer) {
        return reinterpret_cast<LongTradeMessage*>(buffer);
    }

    // parse method const
    static const LongTradeMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const LongTradeMessage*>(buffer);
    }
};

#pragma pack(pop)
}
