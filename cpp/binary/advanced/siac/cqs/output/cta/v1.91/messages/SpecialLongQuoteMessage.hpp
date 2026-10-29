#pragma once

#include <cstddef>
#include "../structs/BlockHeader.hpp"
#include "../structs/SbeGroupSupport.hpp"
#include "../types/ParticipantId.hpp"
#include "../structs/ParticipantTimestamp.hpp"
#include "../types/MessageId.hpp"
#include "../types/TransactionId.hpp"
#include "../types/ParticipantReferenceNumber.hpp"
#include "../types/SecuritySymbolLong.hpp"
#include "../types/InstrumentType.hpp"
#include "../types/QuoteCondition.hpp"
#include "../types/SecurityStatusIndicator.hpp"
#include "../types/BidPriceLong.hpp"
#include "../types/BidSizeLong.hpp"
#include "../types/OfferPriceLong.hpp"
#include "../types/OfferSizeLong.hpp"
#include "../types/RetailInterestIndicator.hpp"
#include "../types/SettlementCondition.hpp"
#include "../types/MarketCondition.hpp"
#include "../types/FinraMarketMakerId.hpp"
#include "../types/FinraBestBidQuoteCondition.hpp"
#include "../types/FinraBestBidPrice.hpp"
#include "../types/FinraBestBidSize.hpp"
#include "../types/FinraBestBidMarketMakerId.hpp"
#include "../types/FinraBestOfferQuoteCondition.hpp"
#include "../types/FinraBestOfferPrice.hpp"
#include "../types/FinraBestOfferSize.hpp"
#include "../types/FinraBestOfferMarketMakerId.hpp"
#include "../structs/AdfTimestamp.hpp"
#include "../types/ShortSaleRestrictionIndicator.hpp"
#include "../types/PrimaryListingMarketParticipantId.hpp"
#include "../types/FinancialStatusIndicator.hpp"
#include "../types/SipGeneratedMessageIdentifier.hpp"
#include "../types/FinraBboLuldIndicator.hpp"
#include "../types/NationalBboLuldIndicator.hpp"
#include "../types/NationalBboIndicator.hpp"
#include "../structs/NationalBestBidLongAppendage.hpp"
#include "../structs/NationalBestOfferLongAppendage.hpp"
#include "../structs/NationalBestBidShortAppendage.hpp"
#include "../structs/NationalBestOfferShortAppendage.hpp"
#include "../types/MessageLength.hpp"
#include "../types/MessageCategory.hpp"
#include "../types/QuoteMessageType.hpp"

namespace siac::cqs::output::cta::v1_91 {

namespace cta_output = ::siac::cqs::output::cta::v1_91;


#pragma pack(push, 1)

// Special Long Quote Message
struct special_long_quote_message {

    struct fields_type {
        cta_output::participant_id participant_id;
        cta_output::participant_timestamp participant_timestamp;
        cta_output::message_id message_id;
        cta_output::transaction_id transaction_id;
        cta_output::participant_reference_number participant_reference_number;
        cta_output::security_symbol_long security_symbol_long;
        cta_output::instrument_type instrument_type;
        cta_output::quote_condition quote_condition;
        cta_output::security_status_indicator security_status_indicator;
        cta_output::bid_price_long bid_price_long;
        cta_output::bid_size_long bid_size_long;
        cta_output::offer_price_long offer_price_long;
        cta_output::offer_size_long offer_size_long;
        cta_output::retail_interest_indicator retail_interest_indicator;
        cta_output::settlement_condition settlement_condition;
        cta_output::market_condition market_condition;
        cta_output::finra_market_maker_id finra_market_maker_id;
        cta_output::finra_best_bid_quote_condition finra_best_bid_quote_condition;
        cta_output::finra_best_bid_price finra_best_bid_price;
        cta_output::finra_best_bid_size finra_best_bid_size;
        cta_output::finra_best_bid_market_maker_id finra_best_bid_market_maker_id;
        cta_output::finra_best_offer_quote_condition finra_best_offer_quote_condition;
        cta_output::finra_best_offer_price finra_best_offer_price;
        cta_output::finra_best_offer_size finra_best_offer_size;
        cta_output::finra_best_offer_market_maker_id finra_best_offer_market_maker_id;
        cta_output::adf_timestamp adf_timestamp;
        cta_output::short_sale_restriction_indicator short_sale_restriction_indicator;
        cta_output::primary_listing_market_participant_id primary_listing_market_participant_id;
        cta_output::financial_status_indicator financial_status_indicator;
        cta_output::sip_generated_message_identifier sip_generated_message_identifier;
        cta_output::finra_bbo_luld_indicator finra_bbo_luld_indicator;
        cta_output::national_bbo_luld_indicator national_bbo_luld_indicator;
        cta_output::national_bbo_indicator national_bbo_indicator;
    };

    cta_output::block_header header = {{}, {}, {}, {}, {}, {}, {}, {}};
    // Transport framing: message size precedes the SBE header on the wire
    cta_output::message_length message_length;
    cta_output::message_category message_category = cta_output::message_category::enum_type::quote;
    cta_output::quote_message_type quote_message_type = cta_output::quote_message_type::enum_type::special_long_quote_message;

    static constexpr std::size_t max_message_size = 1280;
    static constexpr std::size_t tail_capacity = max_message_size - sizeof(cta_output::block_header) - sizeof(fields_type) - sizeof(cta_output::message_length) - sizeof(cta_output::message_category) - sizeof(cta_output::quote_message_type);

    fields_type fields;
    std::byte tail[tail_capacity];

    // tail buffer accessors
    const std::byte* tail_begin() const { return tail; }
    const std::byte* tail_end() const {
        auto sz = message_length.get().value();
        return (sz + sizeof(cta_output::block_header)) == sizeof(cta_output::block_header) + sizeof(fields_type) + sizeof(cta_output::message_length) + sizeof(cta_output::message_category) + sizeof(cta_output::quote_message_type)
            ? tail + tail_capacity
            : tail + ((sz + sizeof(cta_output::block_header)) - sizeof(cta_output::block_header) - sizeof(fields_type) - sizeof(cta_output::message_length) - sizeof(cta_output::message_category) - sizeof(cta_output::quote_message_type));
    }

    // sequential access to variable-length regions
    // optional fixed-size appendage accessors
    const cta_output::national_best_bid_long_appendage* national_best_bid_long_appendage() const {
        return reinterpret_cast<const cta_output::national_best_bid_long_appendage*>(tail_begin());
    }

    const cta_output::national_best_offer_long_appendage* national_best_offer_long_appendage() const {
        return reinterpret_cast<const cta_output::national_best_offer_long_appendage*>(tail_begin());
    }

    const cta_output::national_best_bid_short_appendage* national_best_bid_short_appendage() const {
        return reinterpret_cast<const cta_output::national_best_bid_short_appendage*>(tail_begin());
    }

    const cta_output::national_best_offer_short_appendage* national_best_offer_short_appendage() const {
        return reinterpret_cast<const cta_output::national_best_offer_short_appendage*>(tail_begin());
    }

    // Appendage descriptor — model-driven lookup of which optional
    // appendages are present for each value of the gate field.
    struct appendage_descriptor {
        bool has_bid;
        bool has_offer;
        bool bid_is_long;
        bool offer_is_long;
        std::uint16_t total_bytes;
    };

    static constexpr appendage_descriptor describe_appendages(cta_output::national_bbo_indicator::enum_type code) {
        switch (code) {
            case cta_output::national_bbo_indicator::enum_type::best_bid_short_appendage_best_offer_short_appendage: return { false, true, false, false, static_cast<std::uint16_t>(sizeof(cta_output::national_best_offer_short_appendage)) };
            case cta_output::national_bbo_indicator::enum_type::best_bid_long_appendage_best_offer_long_appendage: return { false, true, false, true, static_cast<std::uint16_t>(sizeof(cta_output::national_best_offer_long_appendage)) };
            default: return { false, false, false, false, 0 };
        }
    }

    constexpr appendage_descriptor describe_appendages() const {
        return describe_appendages(fields.national_bbo_indicator.get().value());
    }


    // parse method
    static special_long_quote_message* parse(std::byte* buffer) {
        return reinterpret_cast<special_long_quote_message*>(buffer);
    }

    // parse method const
    static const special_long_quote_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const special_long_quote_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(special_long_quote_message::fields_type, participant_id) == 0, "unexpected offset of special_long_quote_message::fields_type::participant_id");
static_assert(offsetof(special_long_quote_message::fields_type, participant_timestamp) == 1, "unexpected offset of special_long_quote_message::fields_type::participant_timestamp");
static_assert(offsetof(special_long_quote_message::fields_type, message_id) == 9, "unexpected offset of special_long_quote_message::fields_type::message_id");
static_assert(offsetof(special_long_quote_message::fields_type, transaction_id) == 10, "unexpected offset of special_long_quote_message::fields_type::transaction_id");
static_assert(offsetof(special_long_quote_message::fields_type, participant_reference_number) == 14, "unexpected offset of special_long_quote_message::fields_type::participant_reference_number");
static_assert(offsetof(special_long_quote_message::fields_type, security_symbol_long) == 22, "unexpected offset of special_long_quote_message::fields_type::security_symbol_long");
static_assert(offsetof(special_long_quote_message::fields_type, instrument_type) == 33, "unexpected offset of special_long_quote_message::fields_type::instrument_type");
static_assert(offsetof(special_long_quote_message::fields_type, quote_condition) == 34, "unexpected offset of special_long_quote_message::fields_type::quote_condition");
static_assert(offsetof(special_long_quote_message::fields_type, security_status_indicator) == 35, "unexpected offset of special_long_quote_message::fields_type::security_status_indicator");
static_assert(offsetof(special_long_quote_message::fields_type, bid_price_long) == 36, "unexpected offset of special_long_quote_message::fields_type::bid_price_long");
static_assert(offsetof(special_long_quote_message::fields_type, bid_size_long) == 44, "unexpected offset of special_long_quote_message::fields_type::bid_size_long");
static_assert(offsetof(special_long_quote_message::fields_type, offer_price_long) == 48, "unexpected offset of special_long_quote_message::fields_type::offer_price_long");
static_assert(offsetof(special_long_quote_message::fields_type, offer_size_long) == 56, "unexpected offset of special_long_quote_message::fields_type::offer_size_long");
static_assert(offsetof(special_long_quote_message::fields_type, retail_interest_indicator) == 60, "unexpected offset of special_long_quote_message::fields_type::retail_interest_indicator");
static_assert(offsetof(special_long_quote_message::fields_type, settlement_condition) == 61, "unexpected offset of special_long_quote_message::fields_type::settlement_condition");
static_assert(offsetof(special_long_quote_message::fields_type, market_condition) == 62, "unexpected offset of special_long_quote_message::fields_type::market_condition");
static_assert(offsetof(special_long_quote_message::fields_type, finra_market_maker_id) == 63, "unexpected offset of special_long_quote_message::fields_type::finra_market_maker_id");
static_assert(offsetof(special_long_quote_message::fields_type, finra_best_bid_quote_condition) == 67, "unexpected offset of special_long_quote_message::fields_type::finra_best_bid_quote_condition");
static_assert(offsetof(special_long_quote_message::fields_type, finra_best_bid_price) == 68, "unexpected offset of special_long_quote_message::fields_type::finra_best_bid_price");
static_assert(offsetof(special_long_quote_message::fields_type, finra_best_bid_size) == 76, "unexpected offset of special_long_quote_message::fields_type::finra_best_bid_size");
static_assert(offsetof(special_long_quote_message::fields_type, finra_best_bid_market_maker_id) == 80, "unexpected offset of special_long_quote_message::fields_type::finra_best_bid_market_maker_id");
static_assert(offsetof(special_long_quote_message::fields_type, finra_best_offer_quote_condition) == 84, "unexpected offset of special_long_quote_message::fields_type::finra_best_offer_quote_condition");
static_assert(offsetof(special_long_quote_message::fields_type, finra_best_offer_price) == 85, "unexpected offset of special_long_quote_message::fields_type::finra_best_offer_price");
static_assert(offsetof(special_long_quote_message::fields_type, finra_best_offer_size) == 93, "unexpected offset of special_long_quote_message::fields_type::finra_best_offer_size");
static_assert(offsetof(special_long_quote_message::fields_type, finra_best_offer_market_maker_id) == 97, "unexpected offset of special_long_quote_message::fields_type::finra_best_offer_market_maker_id");
static_assert(offsetof(special_long_quote_message::fields_type, adf_timestamp) == 101, "unexpected offset of special_long_quote_message::fields_type::adf_timestamp");
static_assert(offsetof(special_long_quote_message::fields_type, short_sale_restriction_indicator) == 109, "unexpected offset of special_long_quote_message::fields_type::short_sale_restriction_indicator");
static_assert(offsetof(special_long_quote_message::fields_type, primary_listing_market_participant_id) == 110, "unexpected offset of special_long_quote_message::fields_type::primary_listing_market_participant_id");
static_assert(offsetof(special_long_quote_message::fields_type, financial_status_indicator) == 111, "unexpected offset of special_long_quote_message::fields_type::financial_status_indicator");
static_assert(offsetof(special_long_quote_message::fields_type, sip_generated_message_identifier) == 112, "unexpected offset of special_long_quote_message::fields_type::sip_generated_message_identifier");
static_assert(offsetof(special_long_quote_message::fields_type, finra_bbo_luld_indicator) == 113, "unexpected offset of special_long_quote_message::fields_type::finra_bbo_luld_indicator");
static_assert(offsetof(special_long_quote_message::fields_type, national_bbo_luld_indicator) == 114, "unexpected offset of special_long_quote_message::fields_type::national_bbo_luld_indicator");
static_assert(offsetof(special_long_quote_message::fields_type, national_bbo_indicator) == 115, "unexpected offset of special_long_quote_message::fields_type::national_bbo_indicator");
static_assert(sizeof(special_long_quote_message::fields_type) == 116, "unexpected sizeof special_long_quote_message::fields_type");

#pragma pack(pop)
}
