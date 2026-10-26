#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../structs/SbeGroupSupport.hpp"
#include "../types/BboIndicator.hpp"
#include "../types/TransactionId.hpp"
#include "../types/ParticipantReferenceNumber.hpp"
#include "../types/SecuritySymbol.hpp"
#include "../types/Reserved1.hpp"
#include "../structs/ExpirationBlock.hpp"
#include "../types/StrikePriceDenominatorCode.hpp"
#include "../types/StrikePrice.hpp"
#include "../types/PremiumPriceDenominatorCode.hpp"
#include "../types/BidPrice.hpp"
#include "../types/BidSize.hpp"
#include "../types/OfferPrice.hpp"
#include "../types/OfferSize.hpp"
#include "../structs/BestBidAppendage.hpp"
#include "../structs/BestOfferAppendage.hpp"
#include "../structs/BestBidAndOfferAppendage.hpp"
#include "../types/LongEquityAndIndexQuoteMessageType.hpp"

namespace siac::opra::output::obi::v6_2 {

namespace obi_output = ::siac::opra::output::obi::v6_2;


#pragma pack(push, 1)

// Long Equity And Index Quote Message
struct long_equity_and_index_quote_message {

    struct fields_type {
        obi_output::bbo_indicator bbo_indicator;
        obi_output::transaction_id transaction_id;
        obi_output::participant_reference_number participant_reference_number;
        obi_output::security_symbol security_symbol;
        obi_output::reserved_1 reserved_1;
        obi_output::expiration_block expiration_block;
        obi_output::strike_price_denominator_code strike_price_denominator_code;
        obi_output::strike_price strike_price;
        obi_output::premium_price_denominator_code premium_price_denominator_code;
        obi_output::bid_price bid_price;
        obi_output::bid_size bid_size;
        obi_output::offer_price offer_price;
        obi_output::offer_size offer_size;
    };

    obi_output::message_header header = {{}, message_category::enum_type::long_equity_and_index_quote};
    obi_output::long_equity_and_index_quote_message_type long_equity_and_index_quote_message_type = obi_output::long_equity_and_index_quote_message_type::enum_type::regular_trading;

    static constexpr std::size_t max_message_size = 1280;
    static constexpr std::size_t tail_capacity = max_message_size - sizeof(obi_output::message_header) - sizeof(fields_type) - sizeof(obi_output::long_equity_and_index_quote_message_type);

    fields_type fields;
    std::byte tail[tail_capacity];

    // tail buffer accessors
    const std::byte* tail_begin() const { return tail; }
    const std::byte* tail_end() const { return tail + tail_capacity; }

    // sequential access to variable-length regions
    // optional fixed-size appendage accessors
    const obi_output::best_bid_appendage* best_bid_appendage() const {
        return reinterpret_cast<const obi_output::best_bid_appendage*>(tail_begin());
    }

    const obi_output::best_offer_appendage* best_offer_appendage() const {
        return reinterpret_cast<const obi_output::best_offer_appendage*>(tail_begin());
    }

    const obi_output::best_bid_and_offer_appendage* best_bid_and_offer_appendage() const {
        return reinterpret_cast<const obi_output::best_bid_and_offer_appendage*>(tail_begin());
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

    static constexpr appendage_descriptor describe_appendages(obi_output::bbo_indicator::enum_type code) {
        switch (code) {
            case obi_output::bbo_indicator::enum_type::no_best_bid_change_best_offer_appendage: return { false, true, false, false, static_cast<std::uint16_t>(sizeof(obi_output::best_offer_appendage)) };
            case obi_output::bbo_indicator::enum_type::quote_contains_best_bid_best_offer_appendage: return { false, true, false, false, static_cast<std::uint16_t>(sizeof(obi_output::best_offer_appendage)) };
            case obi_output::bbo_indicator::enum_type::no_best_bid_best_offer_appendage: return { false, true, false, false, static_cast<std::uint16_t>(sizeof(obi_output::best_offer_appendage)) };
            case obi_output::bbo_indicator::enum_type::best_bid_appendage_no_best_offer_change: return { true, false, false, false, static_cast<std::uint16_t>(sizeof(obi_output::best_bid_appendage)) };
            case obi_output::bbo_indicator::enum_type::best_bid_appendage_quote_contains_best_offer: return { true, false, false, false, static_cast<std::uint16_t>(sizeof(obi_output::best_bid_appendage)) };
            case obi_output::bbo_indicator::enum_type::best_bid_appendage_best_offer_appendage: return { true, true, false, false, static_cast<std::uint16_t>(sizeof(obi_output::best_bid_and_offer_appendage)) };
            case obi_output::bbo_indicator::enum_type::best_bid_appendage_no_best_offer: return { true, false, false, false, static_cast<std::uint16_t>(sizeof(obi_output::best_bid_appendage)) };
            default: return { false, false, false, false, 0 };
        }
    }

    constexpr appendage_descriptor describe_appendages() const {
        return describe_appendages(fields.bbo_indicator.get().value());
    }


    // parse method
    static long_equity_and_index_quote_message* parse(std::byte* buffer) {
        return reinterpret_cast<long_equity_and_index_quote_message*>(buffer);
    }

    // parse method const
    static const long_equity_and_index_quote_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const long_equity_and_index_quote_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(long_equity_and_index_quote_message::fields_type, bbo_indicator) == 0, "unexpected offset of long_equity_and_index_quote_message::fields_type::bbo_indicator");
static_assert(offsetof(long_equity_and_index_quote_message::fields_type, transaction_id) == 1, "unexpected offset of long_equity_and_index_quote_message::fields_type::transaction_id");
static_assert(offsetof(long_equity_and_index_quote_message::fields_type, participant_reference_number) == 5, "unexpected offset of long_equity_and_index_quote_message::fields_type::participant_reference_number");
static_assert(offsetof(long_equity_and_index_quote_message::fields_type, security_symbol) == 9, "unexpected offset of long_equity_and_index_quote_message::fields_type::security_symbol");
static_assert(offsetof(long_equity_and_index_quote_message::fields_type, reserved_1) == 14, "unexpected offset of long_equity_and_index_quote_message::fields_type::reserved_1");
static_assert(offsetof(long_equity_and_index_quote_message::fields_type, expiration_block) == 15, "unexpected offset of long_equity_and_index_quote_message::fields_type::expiration_block");
static_assert(offsetof(long_equity_and_index_quote_message::fields_type, strike_price_denominator_code) == 18, "unexpected offset of long_equity_and_index_quote_message::fields_type::strike_price_denominator_code");
static_assert(offsetof(long_equity_and_index_quote_message::fields_type, strike_price) == 19, "unexpected offset of long_equity_and_index_quote_message::fields_type::strike_price");
static_assert(offsetof(long_equity_and_index_quote_message::fields_type, premium_price_denominator_code) == 23, "unexpected offset of long_equity_and_index_quote_message::fields_type::premium_price_denominator_code");
static_assert(offsetof(long_equity_and_index_quote_message::fields_type, bid_price) == 24, "unexpected offset of long_equity_and_index_quote_message::fields_type::bid_price");
static_assert(offsetof(long_equity_and_index_quote_message::fields_type, bid_size) == 28, "unexpected offset of long_equity_and_index_quote_message::fields_type::bid_size");
static_assert(offsetof(long_equity_and_index_quote_message::fields_type, offer_price) == 32, "unexpected offset of long_equity_and_index_quote_message::fields_type::offer_price");
static_assert(offsetof(long_equity_and_index_quote_message::fields_type, offer_size) == 36, "unexpected offset of long_equity_and_index_quote_message::fields_type::offer_size");
static_assert(sizeof(long_equity_and_index_quote_message::fields_type) == 40, "unexpected sizeof long_equity_and_index_quote_message::fields_type");

#pragma pack(pop)
}
