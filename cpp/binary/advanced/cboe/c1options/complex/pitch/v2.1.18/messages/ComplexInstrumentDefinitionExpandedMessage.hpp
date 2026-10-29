#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../structs/SbeGroupSupport.hpp"
#include "../types/TimeOffset.hpp"
#include "../types/ComplexInstrumentId.hpp"
#include "../types/ComplexInstrumentUnderlying.hpp"
#include "../types/ComplexInstrumentType.hpp"
#include "../types/LegCount.hpp"
#include "../types/LegSymbol.hpp"
#include "../types/LegRatio.hpp"
#include "../types/LegSecurityType.hpp"

namespace cboe::c1options::complex::pitch::v2_1_18 {

namespace pitch_complex = ::cboe::c1options::complex::pitch::v2_1_18;

#pragma pack(push, 1)
struct complex_instrument_definition_expanded_message_complex_instrument_leg_entry {
    pitch_complex::leg_symbol leg_symbol;
    pitch_complex::leg_ratio leg_ratio;
    pitch_complex::leg_security_type leg_security_type;
};
#pragma pack(pop)


#pragma pack(push, 1)

// Complex Instrument Definition Expanded Message
struct complex_instrument_definition_expanded_message {

    struct fields_type {
        pitch_complex::time_offset time_offset;
        pitch_complex::complex_instrument_id complex_instrument_id;
        pitch_complex::complex_instrument_underlying complex_instrument_underlying;
        pitch_complex::complex_instrument_type complex_instrument_type;
        pitch_complex::leg_count leg_count;
    };

    pitch_complex::message_header header = {std::uint16_t(sizeof(pitch_complex::message_header) + sizeof(fields_type)), message_type::enum_type::complex_instrument_definition_expanded_message};

    static constexpr std::size_t max_message_size = 1280;
    static constexpr std::size_t tail_capacity = max_message_size - sizeof(pitch_complex::message_header) - sizeof(fields_type);

    fields_type fields;
    std::byte tail[tail_capacity];

    // tail buffer accessors
    const std::byte* tail_begin() const { return tail; }
    const std::byte* tail_end() const {
        auto sz = header.message_length.get().value();
        return sz == sizeof(pitch_complex::message_header) + sizeof(fields_type)
            ? tail + tail_capacity
            : tail + (sz - sizeof(pitch_complex::message_header) - sizeof(fields_type));
    }

    // sequential access to variable-length regions
    external_count_iterator<complex_instrument_definition_expanded_message_complex_instrument_leg_entry> complex_instrument_leg() const {
        return { tail_begin(), fields.leg_count.get().value(), tail_end() };
    }


    // parse method
    static complex_instrument_definition_expanded_message* parse(std::byte* buffer) {
        return reinterpret_cast<complex_instrument_definition_expanded_message*>(buffer);
    }

    // parse method const
    static const complex_instrument_definition_expanded_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const complex_instrument_definition_expanded_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(complex_instrument_definition_expanded_message::fields_type, time_offset) == 0, "unexpected offset of complex_instrument_definition_expanded_message::fields_type::time_offset");
static_assert(offsetof(complex_instrument_definition_expanded_message::fields_type, complex_instrument_id) == 4, "unexpected offset of complex_instrument_definition_expanded_message::fields_type::complex_instrument_id");
static_assert(offsetof(complex_instrument_definition_expanded_message::fields_type, complex_instrument_underlying) == 10, "unexpected offset of complex_instrument_definition_expanded_message::fields_type::complex_instrument_underlying");
static_assert(offsetof(complex_instrument_definition_expanded_message::fields_type, complex_instrument_type) == 18, "unexpected offset of complex_instrument_definition_expanded_message::fields_type::complex_instrument_type");
static_assert(offsetof(complex_instrument_definition_expanded_message::fields_type, leg_count) == 22, "unexpected offset of complex_instrument_definition_expanded_message::fields_type::leg_count");
static_assert(sizeof(complex_instrument_definition_expanded_message::fields_type) == 23, "unexpected sizeof complex_instrument_definition_expanded_message::fields_type");

#pragma pack(pop)
}

#include "details/ComplexInstrumentDefinitionExpandedMessageWriter.hpp"
#include "details/ComplexInstrumentDefinitionExpandedMessageReader.hpp"
