#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/TimeOffset.hpp"
#include "../types/ExpandedSymbol.hpp"
#include "../types/RetailPriceImprovement.hpp"

namespace cboe::c1options::multicastdepthofbook::pitch::v2_39_4 {

namespace pitch_multicastdepthofbook = ::cboe::c1options::multicastdepthofbook::pitch::v2_39_4;

#pragma pack(push, 1)

// Retail Price Improvement Message
struct retail_price_improvement_message {

    struct fields_type {
        pitch_multicastdepthofbook::time_offset time_offset;
        pitch_multicastdepthofbook::expanded_symbol expanded_symbol;
        pitch_multicastdepthofbook::retail_price_improvement retail_price_improvement;
    };

    pitch_multicastdepthofbook::message_header header = {std::uint16_t(sizeof(pitch_multicastdepthofbook::message_header) + sizeof(fields_type)), message_type::enum_type::retail_price_improvement_message};

    fields_type fields;

    // parse method
    static retail_price_improvement_message* parse(std::byte* buffer) {
        return reinterpret_cast<retail_price_improvement_message*>(buffer);
    }

    // parse method const
    static const retail_price_improvement_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const retail_price_improvement_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(retail_price_improvement_message::fields_type, time_offset) == 0, "unexpected offset of retail_price_improvement_message::fields_type::time_offset");
static_assert(offsetof(retail_price_improvement_message::fields_type, expanded_symbol) == 4, "unexpected offset of retail_price_improvement_message::fields_type::expanded_symbol");
static_assert(offsetof(retail_price_improvement_message::fields_type, retail_price_improvement) == 12, "unexpected offset of retail_price_improvement_message::fields_type::retail_price_improvement");
static_assert(sizeof(retail_price_improvement_message::fields_type) == 13, "unexpected sizeof retail_price_improvement_message::fields_type");
static_assert(sizeof(retail_price_improvement_message) == sizeof(pitch_multicastdepthofbook::message_header) + 13, "unexpected sizeof retail_price_improvement_message");

#pragma pack(pop)
}
