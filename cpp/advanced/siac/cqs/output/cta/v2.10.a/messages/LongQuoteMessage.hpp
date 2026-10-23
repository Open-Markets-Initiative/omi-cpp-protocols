#pragma once

#include <cstddef>
#include "../structs/BlockHeader.hpp"
#include "../structs/SbeGroupSupport.hpp"
#include "../types/ParticipantId.hpp"
#include "../structs/Timestamp1.hpp"
#include "../types/MessageId.hpp"
#include "../types/TransactionId.hpp"
#include "../types/ParticipantReferenceNumber.hpp"
#include "../types/SecuritySymbol.hpp"
#include "../types/InstrumentType.hpp"
#include "../types/QuoteCondition.hpp"
#include "../types/SecurityStatusIndicator.hpp"
#include "../types/BidPriceLowerLimitPriceBand.hpp"
#include "../types/BidSizeLong.hpp"
#include "../types/OfferPriceUpperLimitPriceBand.hpp"
#include "../types/OfferSizeLong.hpp"
#include "../types/RetailInterestIndicator.hpp"
#include "../types/SettlementCondition.hpp"
#include "../types/MarketCondition.hpp"
#include "../types/FinraMarketMakerId.hpp"
#include "../types/FinraBboIndicator.hpp"
#include "../types/Timestamp2Optional.hpp"
#include "../types/ShortSaleRestrictionIndicator.hpp"
#include "../types/PrimaryListingMarketParticipantId.hpp"
#include "../types/FinancialStatusIndicator.hpp"
#include "../types/SipGeneratedMessageIdentifier.hpp"
#include "../types/LimitUpLimitDownLuldIndicator.hpp"
#include "../types/NationalBboLuldIndicator.hpp"
#include "../types/NationalBboIndicator.hpp"
#include "../structs/NationalBestBidLongAppendage.hpp"
#include "../structs/NationalBestOfferLongAppendage.hpp"
#include "../structs/NationalBestBidAndOfferLongAppendage.hpp"
#include "../structs/NationalBestBidShortAppendage.hpp"
#include "../structs/NationalBestOfferShortAppendage.hpp"
#include "../structs/NationalBestBidAndOfferShortAppendage.hpp"
#include "../types/MessageLength.hpp"
#include "../types/MessageCategory.hpp"
#include "../types/QuoteMessageType.hpp"

namespace siac::cqs::output::cta::v2_10_a {

namespace cta_output = ::siac::cqs::output::cta::v2_10_a;


#pragma pack(push, 1)

// Long Quote Message
struct long_quote_message {

    struct fields_type {
        cta_output::participant_id participant_id;
        cta_output::timestamp_1 timestamp_1;
        cta_output::message_id message_id;
        cta_output::transaction_id transaction_id;
        cta_output::participant_reference_number participant_reference_number;
        cta_output::security_symbol security_symbol;
        cta_output::instrument_type instrument_type;
        cta_output::quote_condition quote_condition;
        cta_output::security_status_indicator security_status_indicator;
        cta_output::bid_price_lower_limit_price_band bid_price_lower_limit_price_band;
        cta_output::bid_size_long bid_size_long;
        cta_output::offer_price_upper_limit_price_band offer_price_upper_limit_price_band;
        cta_output::offer_size_long offer_size_long;
        cta_output::retail_interest_indicator retail_interest_indicator;
        cta_output::settlement_condition settlement_condition;
        cta_output::market_condition market_condition;
        cta_output::finra_market_maker_id finra_market_maker_id;
        cta_output::finra_bbo_indicator finra_bbo_indicator;
        cta_output::timestamp_2_optional timestamp_2;
        cta_output::short_sale_restriction_indicator short_sale_restriction_indicator;
        cta_output::primary_listing_market_participant_id primary_listing_market_participant_id;
        cta_output::financial_status_indicator financial_status_indicator;
        cta_output::sip_generated_message_identifier sip_generated_message_identifier;
        cta_output::limit_up_limit_down_luld_indicator limit_up_limit_down_luld_indicator;
        cta_output::national_bbo_luld_indicator national_bbo_luld_indicator;
        cta_output::national_bbo_indicator national_bbo_indicator;
    };

    cta_output::block_header header = {{}, {}, {}, {}, {}, {}, {}, {}};
    // Transport framing: message size precedes the SBE header on the wire
    cta_output::message_length message_length;
    cta_output::message_category message_category = cta_output::message_category::enum_type::quote;
    cta_output::quote_message_type quote_message_type = cta_output::quote_message_type::enum_type::long_quote;

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

    const cta_output::national_best_bid_and_offer_long_appendage* national_best_bid_and_offer_long_appendage() const {
        return reinterpret_cast<const cta_output::national_best_bid_and_offer_long_appendage*>(tail_begin());
    }

    const cta_output::national_best_bid_short_appendage* national_best_bid_short_appendage() const {
        return reinterpret_cast<const cta_output::national_best_bid_short_appendage*>(tail_begin());
    }

    const cta_output::national_best_offer_short_appendage* national_best_offer_short_appendage() const {
        return reinterpret_cast<const cta_output::national_best_offer_short_appendage*>(tail_begin());
    }

    const cta_output::national_best_bid_and_offer_short_appendage* national_best_bid_and_offer_short_appendage() const {
        return reinterpret_cast<const cta_output::national_best_bid_and_offer_short_appendage*>(tail_begin());
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
            case cta_output::national_bbo_indicator::enum_type::quote_contains_best_bid_best_offer_short_appendage: return { false, true, false, false, static_cast<std::uint16_t>(sizeof(cta_output::national_best_offer_short_appendage)) };
            case cta_output::national_bbo_indicator::enum_type::quote_contains_best_bid_best_offer_long_appendage: return { false, true, false, true, static_cast<std::uint16_t>(sizeof(cta_output::national_best_offer_long_appendage)) };
            case cta_output::national_bbo_indicator::enum_type::no_best_bid_best_offer_short_appendage: return { false, true, false, false, static_cast<std::uint16_t>(sizeof(cta_output::national_best_offer_short_appendage)) };
            case cta_output::national_bbo_indicator::enum_type::no_best_bid_best_offer_long_appendage: return { false, true, false, true, static_cast<std::uint16_t>(sizeof(cta_output::national_best_offer_long_appendage)) };
            case cta_output::national_bbo_indicator::enum_type::best_bid_short_appendage_no_best_offer_change: return { true, false, false, false, static_cast<std::uint16_t>(sizeof(cta_output::national_best_bid_short_appendage)) };
            case cta_output::national_bbo_indicator::enum_type::best_bid_long_appendage_no_best_offer_change: return { true, false, true, false, static_cast<std::uint16_t>(sizeof(cta_output::national_best_bid_long_appendage)) };
            case cta_output::national_bbo_indicator::enum_type::best_bid_short_appendage_quote_contains_best_offer: return { true, false, false, false, static_cast<std::uint16_t>(sizeof(cta_output::national_best_bid_short_appendage)) };
            case cta_output::national_bbo_indicator::enum_type::best_bid_long_appendage_quote_contains_best_offer: return { true, false, true, false, static_cast<std::uint16_t>(sizeof(cta_output::national_best_bid_long_appendage)) };
            case cta_output::national_bbo_indicator::enum_type::best_bid_short_appendage_best_offer_short_appendage: return { true, true, false, false, static_cast<std::uint16_t>(sizeof(cta_output::national_best_bid_and_offer_short_appendage)) };
            case cta_output::national_bbo_indicator::enum_type::best_bid_long_appendage_best_offer_long_appendage: return { true, true, true, true, static_cast<std::uint16_t>(sizeof(cta_output::national_best_bid_and_offer_long_appendage)) };
            case cta_output::national_bbo_indicator::enum_type::best_bid_short_appendage_no_best_offer: return { true, false, false, false, static_cast<std::uint16_t>(sizeof(cta_output::national_best_bid_short_appendage)) };
            case cta_output::national_bbo_indicator::enum_type::best_bid_long_appendage_no_best_offer: return { true, false, true, false, static_cast<std::uint16_t>(sizeof(cta_output::national_best_bid_long_appendage)) };
            default: return { false, false, false, false, 0 };
        }
    }

    constexpr appendage_descriptor describe_appendages() const {
        return describe_appendages(fields.national_bbo_indicator.get().value());
    }


    // parse method
    static long_quote_message* parse(std::byte* buffer) {
        return reinterpret_cast<long_quote_message*>(buffer);
    }

    // parse method const
    static const long_quote_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const long_quote_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(long_quote_message::fields_type, participant_id) == 0, "unexpected offset of long_quote_message::fields_type::participant_id");
static_assert(offsetof(long_quote_message::fields_type, timestamp_1) == 1, "unexpected offset of long_quote_message::fields_type::timestamp_1");
static_assert(offsetof(long_quote_message::fields_type, message_id) == 9, "unexpected offset of long_quote_message::fields_type::message_id");
static_assert(offsetof(long_quote_message::fields_type, transaction_id) == 10, "unexpected offset of long_quote_message::fields_type::transaction_id");
static_assert(offsetof(long_quote_message::fields_type, participant_reference_number) == 14, "unexpected offset of long_quote_message::fields_type::participant_reference_number");
static_assert(offsetof(long_quote_message::fields_type, security_symbol) == 22, "unexpected offset of long_quote_message::fields_type::security_symbol");
static_assert(offsetof(long_quote_message::fields_type, instrument_type) == 33, "unexpected offset of long_quote_message::fields_type::instrument_type");
static_assert(offsetof(long_quote_message::fields_type, quote_condition) == 34, "unexpected offset of long_quote_message::fields_type::quote_condition");
static_assert(offsetof(long_quote_message::fields_type, security_status_indicator) == 35, "unexpected offset of long_quote_message::fields_type::security_status_indicator");
static_assert(offsetof(long_quote_message::fields_type, bid_price_lower_limit_price_band) == 36, "unexpected offset of long_quote_message::fields_type::bid_price_lower_limit_price_band");
static_assert(offsetof(long_quote_message::fields_type, bid_size_long) == 44, "unexpected offset of long_quote_message::fields_type::bid_size_long");
static_assert(offsetof(long_quote_message::fields_type, offer_price_upper_limit_price_band) == 48, "unexpected offset of long_quote_message::fields_type::offer_price_upper_limit_price_band");
static_assert(offsetof(long_quote_message::fields_type, offer_size_long) == 56, "unexpected offset of long_quote_message::fields_type::offer_size_long");
static_assert(offsetof(long_quote_message::fields_type, retail_interest_indicator) == 60, "unexpected offset of long_quote_message::fields_type::retail_interest_indicator");
static_assert(offsetof(long_quote_message::fields_type, settlement_condition) == 61, "unexpected offset of long_quote_message::fields_type::settlement_condition");
static_assert(offsetof(long_quote_message::fields_type, market_condition) == 62, "unexpected offset of long_quote_message::fields_type::market_condition");
static_assert(offsetof(long_quote_message::fields_type, finra_market_maker_id) == 63, "unexpected offset of long_quote_message::fields_type::finra_market_maker_id");
static_assert(offsetof(long_quote_message::fields_type, finra_bbo_indicator) == 67, "unexpected offset of long_quote_message::fields_type::finra_bbo_indicator");
static_assert(offsetof(long_quote_message::fields_type, timestamp_2) == 68, "unexpected offset of long_quote_message::fields_type::timestamp_2");
static_assert(offsetof(long_quote_message::fields_type, short_sale_restriction_indicator) == 76, "unexpected offset of long_quote_message::fields_type::short_sale_restriction_indicator");
static_assert(offsetof(long_quote_message::fields_type, primary_listing_market_participant_id) == 77, "unexpected offset of long_quote_message::fields_type::primary_listing_market_participant_id");
static_assert(offsetof(long_quote_message::fields_type, financial_status_indicator) == 78, "unexpected offset of long_quote_message::fields_type::financial_status_indicator");
static_assert(offsetof(long_quote_message::fields_type, sip_generated_message_identifier) == 79, "unexpected offset of long_quote_message::fields_type::sip_generated_message_identifier");
static_assert(offsetof(long_quote_message::fields_type, limit_up_limit_down_luld_indicator) == 80, "unexpected offset of long_quote_message::fields_type::limit_up_limit_down_luld_indicator");
static_assert(offsetof(long_quote_message::fields_type, national_bbo_luld_indicator) == 81, "unexpected offset of long_quote_message::fields_type::national_bbo_luld_indicator");
static_assert(offsetof(long_quote_message::fields_type, national_bbo_indicator) == 82, "unexpected offset of long_quote_message::fields_type::national_bbo_indicator");
static_assert(sizeof(long_quote_message::fields_type) == 83, "unexpected sizeof long_quote_message::fields_type");

#pragma pack(pop)
}
