#pragma once

#include <cstddef>
#include "../structs/BlockHeader.hpp"
#include "../types/ParticipantId.hpp"
#include "../structs/Timestamp1.hpp"
#include "../types/MessageId.hpp"
#include "../types/TransactionId.hpp"
#include "../types/ParticipantReferenceNumber.hpp"
#include "../types/SecuritySymbol.hpp"
#include "../types/PriorSecuritySymbol.hpp"
#include "../types/PrimaryListingMarketParticipantId.hpp"
#include "../types/PrimaryListingMarketPreviousClosingPrice.hpp"
#include "../types/ConsolidatedClosingPrice.hpp"
#include "../types/RoundLotSize.hpp"
#include "../types/MinimumPriceIncrementIndicator.hpp"
#include "../types/LuldTier.hpp"
#include "../types/LuldLeverageRatio.hpp"
#include "../types/Test.hpp"
#include "../types/Ipo.hpp"
#include "../types/FinancialStatusIndicator.hpp"
#include "../types/ShortSaleRestrictionIndicator.hpp"
#include "../types/HaltReason.hpp"
#include "../types/InstrumentType.hpp"
#include "../types/Reserved.hpp"
#include "../types/SecondReserved.hpp"
#include "../types/Reserved128.hpp"
#include "../types/MessageLength.hpp"
#include "../types/MessageCategory.hpp"
#include "../types/AdministrativeMessageType.hpp"

namespace siac::cts::output::cta::v2_11_b {

namespace cta_output = ::siac::cts::output::cta::v2_11_b;

#pragma pack(push, 1)

// Symbol Reference Data Message
struct symbol_reference_data_message {

    struct fields_type {
        cta_output::participant_id participant_id;
        cta_output::timestamp_1 timestamp_1;
        cta_output::message_id message_id;
        cta_output::transaction_id transaction_id;
        cta_output::participant_reference_number participant_reference_number;
        cta_output::security_symbol security_symbol;
        cta_output::prior_security_symbol prior_security_symbol;
        cta_output::primary_listing_market_participant_id primary_listing_market_participant_id;
        cta_output::primary_listing_market_previous_closing_price primary_listing_market_previous_closing_price;
        cta_output::consolidated_closing_price consolidated_closing_price;
        cta_output::round_lot_size round_lot_size;
        cta_output::minimum_price_increment_indicator minimum_price_increment_indicator;
        cta_output::luld_tier luld_tier;
        cta_output::luld_leverage_ratio luld_leverage_ratio;
        cta_output::test test;
        cta_output::ipo ipo;
        cta_output::financial_status_indicator financial_status_indicator;
        cta_output::short_sale_restriction_indicator short_sale_restriction_indicator;
        cta_output::halt_reason halt_reason;
        cta_output::instrument_type instrument_type;
        cta_output::reserved reserved;
        cta_output::second_reserved second_reserved;
        cta_output::reserved_128 reserved_128;
    };

    cta_output::block_header header = {{}, {}, {}, {}, {}, {}, {}, {}};
    // Transport framing: message size precedes the SBE header on the wire
    cta_output::message_length message_length;
    cta_output::message_category message_category = cta_output::message_category::enum_type::administrative;
    cta_output::administrative_message_type administrative_message_type = cta_output::administrative_message_type::enum_type::symbol_reference_data;

    fields_type fields;

    // parse method
    static symbol_reference_data_message* parse(std::byte* buffer) {
        return reinterpret_cast<symbol_reference_data_message*>(buffer);
    }

    // parse method const
    static const symbol_reference_data_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const symbol_reference_data_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(symbol_reference_data_message::fields_type, participant_id) == 0, "unexpected offset of symbol_reference_data_message::fields_type::participant_id");
static_assert(offsetof(symbol_reference_data_message::fields_type, timestamp_1) == 1, "unexpected offset of symbol_reference_data_message::fields_type::timestamp_1");
static_assert(offsetof(symbol_reference_data_message::fields_type, message_id) == 9, "unexpected offset of symbol_reference_data_message::fields_type::message_id");
static_assert(offsetof(symbol_reference_data_message::fields_type, transaction_id) == 10, "unexpected offset of symbol_reference_data_message::fields_type::transaction_id");
static_assert(offsetof(symbol_reference_data_message::fields_type, participant_reference_number) == 14, "unexpected offset of symbol_reference_data_message::fields_type::participant_reference_number");
static_assert(offsetof(symbol_reference_data_message::fields_type, security_symbol) == 22, "unexpected offset of symbol_reference_data_message::fields_type::security_symbol");
static_assert(offsetof(symbol_reference_data_message::fields_type, prior_security_symbol) == 33, "unexpected offset of symbol_reference_data_message::fields_type::prior_security_symbol");
static_assert(offsetof(symbol_reference_data_message::fields_type, primary_listing_market_participant_id) == 44, "unexpected offset of symbol_reference_data_message::fields_type::primary_listing_market_participant_id");
static_assert(offsetof(symbol_reference_data_message::fields_type, primary_listing_market_previous_closing_price) == 45, "unexpected offset of symbol_reference_data_message::fields_type::primary_listing_market_previous_closing_price");
static_assert(offsetof(symbol_reference_data_message::fields_type, consolidated_closing_price) == 53, "unexpected offset of symbol_reference_data_message::fields_type::consolidated_closing_price");
static_assert(offsetof(symbol_reference_data_message::fields_type, round_lot_size) == 61, "unexpected offset of symbol_reference_data_message::fields_type::round_lot_size");
static_assert(offsetof(symbol_reference_data_message::fields_type, minimum_price_increment_indicator) == 63, "unexpected offset of symbol_reference_data_message::fields_type::minimum_price_increment_indicator");
static_assert(offsetof(symbol_reference_data_message::fields_type, luld_tier) == 64, "unexpected offset of symbol_reference_data_message::fields_type::luld_tier");
static_assert(offsetof(symbol_reference_data_message::fields_type, luld_leverage_ratio) == 65, "unexpected offset of symbol_reference_data_message::fields_type::luld_leverage_ratio");
static_assert(offsetof(symbol_reference_data_message::fields_type, test) == 69, "unexpected offset of symbol_reference_data_message::fields_type::test");
static_assert(offsetof(symbol_reference_data_message::fields_type, ipo) == 70, "unexpected offset of symbol_reference_data_message::fields_type::ipo");
static_assert(offsetof(symbol_reference_data_message::fields_type, financial_status_indicator) == 71, "unexpected offset of symbol_reference_data_message::fields_type::financial_status_indicator");
static_assert(offsetof(symbol_reference_data_message::fields_type, short_sale_restriction_indicator) == 72, "unexpected offset of symbol_reference_data_message::fields_type::short_sale_restriction_indicator");
static_assert(offsetof(symbol_reference_data_message::fields_type, halt_reason) == 73, "unexpected offset of symbol_reference_data_message::fields_type::halt_reason");
static_assert(offsetof(symbol_reference_data_message::fields_type, instrument_type) == 74, "unexpected offset of symbol_reference_data_message::fields_type::instrument_type");
static_assert(offsetof(symbol_reference_data_message::fields_type, reserved) == 75, "unexpected offset of symbol_reference_data_message::fields_type::reserved");
static_assert(offsetof(symbol_reference_data_message::fields_type, second_reserved) == 76, "unexpected offset of symbol_reference_data_message::fields_type::second_reserved");
static_assert(offsetof(symbol_reference_data_message::fields_type, reserved_128) == 77, "unexpected offset of symbol_reference_data_message::fields_type::reserved_128");
static_assert(sizeof(symbol_reference_data_message::fields_type) == 205, "unexpected sizeof symbol_reference_data_message::fields_type");
static_assert(sizeof(symbol_reference_data_message) == sizeof(cta_output::block_header) + sizeof(cta_output::message_length) + sizeof(cta_output::message_category) + sizeof(cta_output::administrative_message_type) + 205, "unexpected sizeof symbol_reference_data_message");

#pragma pack(pop)
}
