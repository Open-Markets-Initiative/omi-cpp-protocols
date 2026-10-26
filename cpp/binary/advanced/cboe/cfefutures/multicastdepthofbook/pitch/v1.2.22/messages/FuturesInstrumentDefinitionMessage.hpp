#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../structs/SbeGroupSupport.hpp"
#include "../types/TimeOffset.hpp"
#include "../types/Symbol.hpp"
#include "../types/UnitTimestamp.hpp"
#include "../types/ReportSymbol.hpp"
#include "../types/FuturesFlags.hpp"
#include "../types/ExpirationDate.hpp"
#include "../types/ContractSize.hpp"
#include "../types/ListingState.hpp"
#include "../types/PriceIncrement.hpp"
#include "../types/LegCount.hpp"
#include "../types/LegOffset.hpp"
#include "../types/Reserved1.hpp"
#include "../types/ContractDate.hpp"
#include "../types/LegRatio.hpp"
#include "../types/LegSymbol.hpp"

namespace cboe::cfefutures::multicastdepthofbook::pitch::v1_2_22 {

namespace pitch_multicastdepthofbook = ::cboe::cfefutures::multicastdepthofbook::pitch::v1_2_22;

#pragma pack(push, 1)
struct futures_instrument_definition_message_future_leg_entry {
    pitch_multicastdepthofbook::leg_ratio leg_ratio;
    pitch_multicastdepthofbook::leg_symbol leg_symbol;
};
#pragma pack(pop)


#pragma pack(push, 1)

// Futures Instrument Definition Message
struct futures_instrument_definition_message {

    struct fields_type {
        pitch_multicastdepthofbook::time_offset time_offset;
        pitch_multicastdepthofbook::symbol symbol;
        pitch_multicastdepthofbook::unit_timestamp unit_timestamp;
        pitch_multicastdepthofbook::report_symbol report_symbol;
        pitch_multicastdepthofbook::futures_flags futures_flags;
        pitch_multicastdepthofbook::expiration_date expiration_date;
        pitch_multicastdepthofbook::contract_size contract_size;
        pitch_multicastdepthofbook::listing_state listing_state;
        pitch_multicastdepthofbook::price_increment price_increment;
        pitch_multicastdepthofbook::leg_count leg_count;
        pitch_multicastdepthofbook::leg_offset leg_offset;
        pitch_multicastdepthofbook::reserved_1 reserved_1;
        pitch_multicastdepthofbook::contract_date contract_date;
    };

    pitch_multicastdepthofbook::message_header header = {std::uint16_t(sizeof(pitch_multicastdepthofbook::message_header) + sizeof(fields_type)), message_type::enum_type::futures_instrument_definition_message};

    static constexpr std::size_t max_message_size = 1280;
    static constexpr std::size_t tail_capacity = max_message_size - sizeof(pitch_multicastdepthofbook::message_header) - sizeof(fields_type);

    fields_type fields;
    std::byte tail[tail_capacity];

    // tail buffer accessors
    const std::byte* tail_begin() const { return tail; }
    const std::byte* tail_end() const {
        auto sz = header.message_length.get().value();
        return sz == sizeof(pitch_multicastdepthofbook::message_header) + sizeof(fields_type)
            ? tail + tail_capacity
            : tail + (sz - sizeof(pitch_multicastdepthofbook::message_header) - sizeof(fields_type));
    }

    // sequential access to variable-length regions
    external_count_iterator<futures_instrument_definition_message_future_leg_entry> future_leg() const {
        return { tail_begin(), fields.leg_count.get().value(), tail_end() };
    }


    // parse method
    static futures_instrument_definition_message* parse(std::byte* buffer) {
        return reinterpret_cast<futures_instrument_definition_message*>(buffer);
    }

    // parse method const
    static const futures_instrument_definition_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const futures_instrument_definition_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(futures_instrument_definition_message::fields_type, time_offset) == 0, "unexpected offset of futures_instrument_definition_message::fields_type::time_offset");
static_assert(offsetof(futures_instrument_definition_message::fields_type, symbol) == 4, "unexpected offset of futures_instrument_definition_message::fields_type::symbol");
static_assert(offsetof(futures_instrument_definition_message::fields_type, unit_timestamp) == 10, "unexpected offset of futures_instrument_definition_message::fields_type::unit_timestamp");
static_assert(offsetof(futures_instrument_definition_message::fields_type, report_symbol) == 14, "unexpected offset of futures_instrument_definition_message::fields_type::report_symbol");
static_assert(offsetof(futures_instrument_definition_message::fields_type, futures_flags) == 20, "unexpected offset of futures_instrument_definition_message::fields_type::futures_flags");
static_assert(offsetof(futures_instrument_definition_message::fields_type, expiration_date) == 21, "unexpected offset of futures_instrument_definition_message::fields_type::expiration_date");
static_assert(offsetof(futures_instrument_definition_message::fields_type, contract_size) == 25, "unexpected offset of futures_instrument_definition_message::fields_type::contract_size");
static_assert(offsetof(futures_instrument_definition_message::fields_type, listing_state) == 27, "unexpected offset of futures_instrument_definition_message::fields_type::listing_state");
static_assert(offsetof(futures_instrument_definition_message::fields_type, price_increment) == 28, "unexpected offset of futures_instrument_definition_message::fields_type::price_increment");
static_assert(offsetof(futures_instrument_definition_message::fields_type, leg_count) == 36, "unexpected offset of futures_instrument_definition_message::fields_type::leg_count");
static_assert(offsetof(futures_instrument_definition_message::fields_type, leg_offset) == 37, "unexpected offset of futures_instrument_definition_message::fields_type::leg_offset");
static_assert(offsetof(futures_instrument_definition_message::fields_type, reserved_1) == 38, "unexpected offset of futures_instrument_definition_message::fields_type::reserved_1");
static_assert(offsetof(futures_instrument_definition_message::fields_type, contract_date) == 39, "unexpected offset of futures_instrument_definition_message::fields_type::contract_date");
static_assert(sizeof(futures_instrument_definition_message::fields_type) == 43, "unexpected sizeof futures_instrument_definition_message::fields_type");

#pragma pack(pop)
}

#include "details/FuturesInstrumentDefinitionMessageWriter.hpp"
#include "details/FuturesInstrumentDefinitionMessageReader.hpp"
