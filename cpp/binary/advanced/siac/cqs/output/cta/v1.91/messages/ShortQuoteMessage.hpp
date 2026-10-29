#pragma once

#include <cstddef>
#include "../structs/BlockHeader.hpp"
#include "../structs/SbeGroupSupport.hpp"
#include "../types/ParticipantId.hpp"
#include "../structs/ParticipantTimestamp.hpp"
#include "../types/MessageId.hpp"
#include "../types/TransactionId.hpp"
#include "../types/ParticipantReferenceNumber.hpp"
#include "../types/SecuritySymbolShort.hpp"
#include "../types/BidPriceShort.hpp"
#include "../types/BidSizeShort.hpp"
#include "../types/OfferPriceShort.hpp"
#include "../types/OfferSizeShort.hpp"
#include "../types/PrimaryListingMarketParticipantId.hpp"
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

// Short Quote Message
struct short_quote_message {

    struct fields_type {
        cta_output::participant_id participant_id;
        cta_output::participant_timestamp participant_timestamp;
        cta_output::message_id message_id;
        cta_output::transaction_id transaction_id;
        cta_output::participant_reference_number participant_reference_number;
        cta_output::security_symbol_short security_symbol_short;
        cta_output::bid_price_short bid_price_short;
        cta_output::bid_size_short bid_size_short;
        cta_output::offer_price_short offer_price_short;
        cta_output::offer_size_short offer_size_short;
        cta_output::primary_listing_market_participant_id primary_listing_market_participant_id;
        cta_output::national_bbo_indicator national_bbo_indicator;
    };

    cta_output::block_header header = {{}, {}, {}, {}, {}, {}, {}, {}};
    // Transport framing: message size precedes the SBE header on the wire
    cta_output::message_length message_length;
    cta_output::message_category message_category = cta_output::message_category::enum_type::quote;
    cta_output::quote_message_type quote_message_type = cta_output::quote_message_type::enum_type::short_quote_message;

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
    static short_quote_message* parse(std::byte* buffer) {
        return reinterpret_cast<short_quote_message*>(buffer);
    }

    // parse method const
    static const short_quote_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const short_quote_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(short_quote_message::fields_type, participant_id) == 0, "unexpected offset of short_quote_message::fields_type::participant_id");
static_assert(offsetof(short_quote_message::fields_type, participant_timestamp) == 1, "unexpected offset of short_quote_message::fields_type::participant_timestamp");
static_assert(offsetof(short_quote_message::fields_type, message_id) == 9, "unexpected offset of short_quote_message::fields_type::message_id");
static_assert(offsetof(short_quote_message::fields_type, transaction_id) == 10, "unexpected offset of short_quote_message::fields_type::transaction_id");
static_assert(offsetof(short_quote_message::fields_type, participant_reference_number) == 14, "unexpected offset of short_quote_message::fields_type::participant_reference_number");
static_assert(offsetof(short_quote_message::fields_type, security_symbol_short) == 22, "unexpected offset of short_quote_message::fields_type::security_symbol_short");
static_assert(offsetof(short_quote_message::fields_type, bid_price_short) == 27, "unexpected offset of short_quote_message::fields_type::bid_price_short");
static_assert(offsetof(short_quote_message::fields_type, bid_size_short) == 29, "unexpected offset of short_quote_message::fields_type::bid_size_short");
static_assert(offsetof(short_quote_message::fields_type, offer_price_short) == 31, "unexpected offset of short_quote_message::fields_type::offer_price_short");
static_assert(offsetof(short_quote_message::fields_type, offer_size_short) == 33, "unexpected offset of short_quote_message::fields_type::offer_size_short");
static_assert(offsetof(short_quote_message::fields_type, primary_listing_market_participant_id) == 35, "unexpected offset of short_quote_message::fields_type::primary_listing_market_participant_id");
static_assert(offsetof(short_quote_message::fields_type, national_bbo_indicator) == 36, "unexpected offset of short_quote_message::fields_type::national_bbo_indicator");
static_assert(sizeof(short_quote_message::fields_type) == 37, "unexpected sizeof short_quote_message::fields_type");

#pragma pack(pop)
}
