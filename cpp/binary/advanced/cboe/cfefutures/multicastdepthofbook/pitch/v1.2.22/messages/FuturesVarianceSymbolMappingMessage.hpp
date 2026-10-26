#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/TimeOffset.hpp"
#include "../types/UnitTimestamp.hpp"
#include "../types/FeedSymbol.hpp"
#include "../types/FuturesSymbol.hpp"
#include "../types/AccruedDayVariance.hpp"
#include "../types/NumFinalReturns.hpp"
#include "../types/NumElapsedReturns.hpp"

namespace cboe::cfefutures::multicastdepthofbook::pitch::v1_2_22 {

namespace pitch_multicastdepthofbook = ::cboe::cfefutures::multicastdepthofbook::pitch::v1_2_22;

#pragma pack(push, 1)

// Futures Variance Symbol Mapping Message
struct futures_variance_symbol_mapping_message {

    struct fields_type {
        pitch_multicastdepthofbook::time_offset time_offset;
        pitch_multicastdepthofbook::unit_timestamp unit_timestamp;
        pitch_multicastdepthofbook::feed_symbol feed_symbol;
        pitch_multicastdepthofbook::futures_symbol futures_symbol;
        pitch_multicastdepthofbook::accrued_day_variance accrued_day_variance;
        pitch_multicastdepthofbook::num_final_returns num_final_returns;
        pitch_multicastdepthofbook::num_elapsed_returns num_elapsed_returns;
    };

    pitch_multicastdepthofbook::message_header header = {std::uint16_t(sizeof(pitch_multicastdepthofbook::message_header) + sizeof(fields_type)), message_type::enum_type::futures_variance_symbol_mapping_message};

    fields_type fields;

    // parse method
    static futures_variance_symbol_mapping_message* parse(std::byte* buffer) {
        return reinterpret_cast<futures_variance_symbol_mapping_message*>(buffer);
    }

    // parse method const
    static const futures_variance_symbol_mapping_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const futures_variance_symbol_mapping_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(futures_variance_symbol_mapping_message::fields_type, time_offset) == 0, "unexpected offset of futures_variance_symbol_mapping_message::fields_type::time_offset");
static_assert(offsetof(futures_variance_symbol_mapping_message::fields_type, unit_timestamp) == 4, "unexpected offset of futures_variance_symbol_mapping_message::fields_type::unit_timestamp");
static_assert(offsetof(futures_variance_symbol_mapping_message::fields_type, feed_symbol) == 8, "unexpected offset of futures_variance_symbol_mapping_message::fields_type::feed_symbol");
static_assert(offsetof(futures_variance_symbol_mapping_message::fields_type, futures_symbol) == 14, "unexpected offset of futures_variance_symbol_mapping_message::fields_type::futures_symbol");
static_assert(offsetof(futures_variance_symbol_mapping_message::fields_type, accrued_day_variance) == 26, "unexpected offset of futures_variance_symbol_mapping_message::fields_type::accrued_day_variance");
static_assert(offsetof(futures_variance_symbol_mapping_message::fields_type, num_final_returns) == 34, "unexpected offset of futures_variance_symbol_mapping_message::fields_type::num_final_returns");
static_assert(offsetof(futures_variance_symbol_mapping_message::fields_type, num_elapsed_returns) == 36, "unexpected offset of futures_variance_symbol_mapping_message::fields_type::num_elapsed_returns");
static_assert(sizeof(futures_variance_symbol_mapping_message::fields_type) == 38, "unexpected sizeof futures_variance_symbol_mapping_message::fields_type");
static_assert(sizeof(futures_variance_symbol_mapping_message) == sizeof(pitch_multicastdepthofbook::message_header) + 38, "unexpected sizeof futures_variance_symbol_mapping_message");

#pragma pack(pop)
}
