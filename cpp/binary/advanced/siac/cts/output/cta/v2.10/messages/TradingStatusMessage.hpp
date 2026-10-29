#pragma once

#include <cstddef>
#include "../structs/BlockHeader.hpp"
#include "../types/ParticipantId.hpp"
#include "../structs/Timestamp1.hpp"
#include "../types/MessageId.hpp"
#include "../types/TransactionId.hpp"
#include "../types/ParticipantReferenceNumber.hpp"
#include "../types/SecuritySymbol.hpp"
#include "../types/InstrumentType.hpp"
#include "../types/LastPrice.hpp"
#include "../types/HighIndicationPriceUpperLimitPriceBand.hpp"
#include "../types/LowIndicationPriceLowerLimitPriceBand.hpp"
#include "../types/BuyVolume.hpp"
#include "../types/SellVolume.hpp"
#include "../types/SecurityStatus.hpp"
#include "../types/HaltReason.hpp"
#include "../types/ShortSaleRestrictionIndicator.hpp"
#include "../types/PrimaryListingMarketParticipantId.hpp"
#include "../types/FinancialStatusIndicator.hpp"
#include "../types/LimitUpLimitDownIndicator.hpp"
#include "../types/MessageLength.hpp"
#include "../types/MessageCategory.hpp"
#include "../types/TradeMessageType.hpp"

namespace siac::cts::output::cta::v2_10 {

namespace cta_output = ::siac::cts::output::cta::v2_10;

#pragma pack(push, 1)

// Trading Status Message
struct trading_status_message {

    struct fields_type {
        cta_output::participant_id participant_id;
        cta_output::timestamp_1 timestamp_1;
        cta_output::message_id message_id;
        cta_output::transaction_id transaction_id;
        cta_output::participant_reference_number participant_reference_number;
        cta_output::security_symbol security_symbol;
        cta_output::instrument_type instrument_type;
        cta_output::last_price last_price;
        cta_output::high_indication_price_upper_limit_price_band high_indication_price_upper_limit_price_band;
        cta_output::low_indication_price_lower_limit_price_band low_indication_price_lower_limit_price_band;
        cta_output::buy_volume buy_volume;
        cta_output::sell_volume sell_volume;
        cta_output::security_status security_status;
        cta_output::halt_reason halt_reason;
        cta_output::short_sale_restriction_indicator short_sale_restriction_indicator;
        cta_output::primary_listing_market_participant_id primary_listing_market_participant_id;
        cta_output::financial_status_indicator financial_status_indicator;
        cta_output::limit_up_limit_down_indicator limit_up_limit_down_indicator;
    };

    cta_output::block_header header = {{}, {}, {}, {}, {}, {}, {}, {}};
    // Transport framing: message size precedes the SBE header on the wire
    cta_output::message_length message_length;
    cta_output::message_category message_category = cta_output::message_category::enum_type::trade;
    cta_output::trade_message_type trade_message_type = cta_output::trade_message_type::enum_type::trading_status_message;

    fields_type fields;

    // parse method
    static trading_status_message* parse(std::byte* buffer) {
        return reinterpret_cast<trading_status_message*>(buffer);
    }

    // parse method const
    static const trading_status_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const trading_status_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(trading_status_message::fields_type, participant_id) == 0, "unexpected offset of trading_status_message::fields_type::participant_id");
static_assert(offsetof(trading_status_message::fields_type, timestamp_1) == 1, "unexpected offset of trading_status_message::fields_type::timestamp_1");
static_assert(offsetof(trading_status_message::fields_type, message_id) == 9, "unexpected offset of trading_status_message::fields_type::message_id");
static_assert(offsetof(trading_status_message::fields_type, transaction_id) == 10, "unexpected offset of trading_status_message::fields_type::transaction_id");
static_assert(offsetof(trading_status_message::fields_type, participant_reference_number) == 14, "unexpected offset of trading_status_message::fields_type::participant_reference_number");
static_assert(offsetof(trading_status_message::fields_type, security_symbol) == 22, "unexpected offset of trading_status_message::fields_type::security_symbol");
static_assert(offsetof(trading_status_message::fields_type, instrument_type) == 33, "unexpected offset of trading_status_message::fields_type::instrument_type");
static_assert(offsetof(trading_status_message::fields_type, last_price) == 34, "unexpected offset of trading_status_message::fields_type::last_price");
static_assert(offsetof(trading_status_message::fields_type, high_indication_price_upper_limit_price_band) == 42, "unexpected offset of trading_status_message::fields_type::high_indication_price_upper_limit_price_band");
static_assert(offsetof(trading_status_message::fields_type, low_indication_price_lower_limit_price_band) == 50, "unexpected offset of trading_status_message::fields_type::low_indication_price_lower_limit_price_band");
static_assert(offsetof(trading_status_message::fields_type, buy_volume) == 58, "unexpected offset of trading_status_message::fields_type::buy_volume");
static_assert(offsetof(trading_status_message::fields_type, sell_volume) == 62, "unexpected offset of trading_status_message::fields_type::sell_volume");
static_assert(offsetof(trading_status_message::fields_type, security_status) == 66, "unexpected offset of trading_status_message::fields_type::security_status");
static_assert(offsetof(trading_status_message::fields_type, halt_reason) == 67, "unexpected offset of trading_status_message::fields_type::halt_reason");
static_assert(offsetof(trading_status_message::fields_type, short_sale_restriction_indicator) == 68, "unexpected offset of trading_status_message::fields_type::short_sale_restriction_indicator");
static_assert(offsetof(trading_status_message::fields_type, primary_listing_market_participant_id) == 69, "unexpected offset of trading_status_message::fields_type::primary_listing_market_participant_id");
static_assert(offsetof(trading_status_message::fields_type, financial_status_indicator) == 70, "unexpected offset of trading_status_message::fields_type::financial_status_indicator");
static_assert(offsetof(trading_status_message::fields_type, limit_up_limit_down_indicator) == 71, "unexpected offset of trading_status_message::fields_type::limit_up_limit_down_indicator");
static_assert(sizeof(trading_status_message::fields_type) == 72, "unexpected sizeof trading_status_message::fields_type");
static_assert(sizeof(trading_status_message) == sizeof(cta_output::block_header) + sizeof(cta_output::message_length) + sizeof(cta_output::message_category) + sizeof(cta_output::trade_message_type) + 72, "unexpected sizeof trading_status_message");

#pragma pack(pop)
}
