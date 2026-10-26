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
#include "../types/AuctionCollarReferencePrice.hpp"
#include "../types/AuctionCollarUpperThresholdPrice.hpp"
#include "../types/AuctionCollarLowerThresholdPrice.hpp"
#include "../types/NumberOfExtensions.hpp"
#include "../types/ShortSaleRestrictionIndicator.hpp"
#include "../types/PrimaryListingMarketParticipantId.hpp"
#include "../types/FinancialStatusIndicator.hpp"
#include "../types/Reserved62.hpp"
#include "../types/MessageLength.hpp"
#include "../types/MessageCategory.hpp"
#include "../types/TradeMessageType.hpp"

namespace siac::cts::output::cta::v2_11_b {

namespace cta_output = ::siac::cts::output::cta::v2_11_b;

#pragma pack(push, 1)

// Auction Status Message
struct auction_status_message {

    struct fields_type {
        cta_output::participant_id participant_id;
        cta_output::timestamp_1 timestamp_1;
        cta_output::message_id message_id;
        cta_output::transaction_id transaction_id;
        cta_output::participant_reference_number participant_reference_number;
        cta_output::security_symbol security_symbol;
        cta_output::instrument_type instrument_type;
        cta_output::auction_collar_reference_price auction_collar_reference_price;
        cta_output::auction_collar_upper_threshold_price auction_collar_upper_threshold_price;
        cta_output::auction_collar_lower_threshold_price auction_collar_lower_threshold_price;
        cta_output::number_of_extensions number_of_extensions;
        cta_output::short_sale_restriction_indicator short_sale_restriction_indicator;
        cta_output::primary_listing_market_participant_id primary_listing_market_participant_id;
        cta_output::financial_status_indicator financial_status_indicator;
        cta_output::reserved_62 reserved_62;
    };

    cta_output::block_header header = {{}, {}, {}, {}, {}, {}, {}, {}};
    // Transport framing: message size precedes the SBE header on the wire
    cta_output::message_length message_length;
    cta_output::message_category message_category = cta_output::message_category::enum_type::trade;
    cta_output::trade_message_type trade_message_type = cta_output::trade_message_type::enum_type::auction_status;

    fields_type fields;

    // parse method
    static auction_status_message* parse(std::byte* buffer) {
        return reinterpret_cast<auction_status_message*>(buffer);
    }

    // parse method const
    static const auction_status_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const auction_status_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(auction_status_message::fields_type, participant_id) == 0, "unexpected offset of auction_status_message::fields_type::participant_id");
static_assert(offsetof(auction_status_message::fields_type, timestamp_1) == 1, "unexpected offset of auction_status_message::fields_type::timestamp_1");
static_assert(offsetof(auction_status_message::fields_type, message_id) == 9, "unexpected offset of auction_status_message::fields_type::message_id");
static_assert(offsetof(auction_status_message::fields_type, transaction_id) == 10, "unexpected offset of auction_status_message::fields_type::transaction_id");
static_assert(offsetof(auction_status_message::fields_type, participant_reference_number) == 14, "unexpected offset of auction_status_message::fields_type::participant_reference_number");
static_assert(offsetof(auction_status_message::fields_type, security_symbol) == 22, "unexpected offset of auction_status_message::fields_type::security_symbol");
static_assert(offsetof(auction_status_message::fields_type, instrument_type) == 33, "unexpected offset of auction_status_message::fields_type::instrument_type");
static_assert(offsetof(auction_status_message::fields_type, auction_collar_reference_price) == 34, "unexpected offset of auction_status_message::fields_type::auction_collar_reference_price");
static_assert(offsetof(auction_status_message::fields_type, auction_collar_upper_threshold_price) == 42, "unexpected offset of auction_status_message::fields_type::auction_collar_upper_threshold_price");
static_assert(offsetof(auction_status_message::fields_type, auction_collar_lower_threshold_price) == 50, "unexpected offset of auction_status_message::fields_type::auction_collar_lower_threshold_price");
static_assert(offsetof(auction_status_message::fields_type, number_of_extensions) == 58, "unexpected offset of auction_status_message::fields_type::number_of_extensions");
static_assert(offsetof(auction_status_message::fields_type, short_sale_restriction_indicator) == 59, "unexpected offset of auction_status_message::fields_type::short_sale_restriction_indicator");
static_assert(offsetof(auction_status_message::fields_type, primary_listing_market_participant_id) == 60, "unexpected offset of auction_status_message::fields_type::primary_listing_market_participant_id");
static_assert(offsetof(auction_status_message::fields_type, financial_status_indicator) == 61, "unexpected offset of auction_status_message::fields_type::financial_status_indicator");
static_assert(offsetof(auction_status_message::fields_type, reserved_62) == 62, "unexpected offset of auction_status_message::fields_type::reserved_62");
static_assert(sizeof(auction_status_message::fields_type) == 124, "unexpected sizeof auction_status_message::fields_type");
static_assert(sizeof(auction_status_message) == sizeof(cta_output::block_header) + sizeof(cta_output::message_length) + sizeof(cta_output::message_category) + sizeof(cta_output::trade_message_type) + 124, "unexpected sizeof auction_status_message");

#pragma pack(pop)
}
