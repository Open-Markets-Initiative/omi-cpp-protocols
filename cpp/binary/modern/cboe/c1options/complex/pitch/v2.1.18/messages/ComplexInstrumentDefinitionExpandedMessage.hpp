#pragma once

#include "../types/TimeOffset.hpp"
#include "../types/ComplexInstrumentId.hpp"
#include "../types/ComplexInstrumentUnderlying.hpp"
#include "../types/ComplexInstrumentType.hpp"
#include "../types/LegCount.hpp"
#include "../structs/MessageHeader.hpp"

namespace cboe::c1options::complex::pitch::v2_1_18 {

#pragma pack(push, 1)

// A Complex Instrument Definition Expanded message represents a complex instrument that is available to place orders.
struct ComplexInstrumentDefinitionExpandedMessage {

    TimeOffset time_offset;
    ComplexInstrumentId complex_instrument_id;
    ComplexInstrumentUnderlying complex_instrument_underlying;
    ComplexInstrumentType complex_instrument_type;
    LegCount leg_count;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint8_t message_type = 0x9A;

    // parse method
    static ComplexInstrumentDefinitionExpandedMessage* parse(std::byte* buffer) {
        return reinterpret_cast<ComplexInstrumentDefinitionExpandedMessage*>(buffer);
    }

    // parse method const
    static const ComplexInstrumentDefinitionExpandedMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const ComplexInstrumentDefinitionExpandedMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const ComplexInstrumentDefinitionExpandedMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const ComplexInstrumentDefinitionExpandedMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
