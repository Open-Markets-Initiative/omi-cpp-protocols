#pragma once

#include "../definitions.hpp"

namespace cboe::c1options::complex::pitch::v2_1_18 {
// ComplexInstrumentLegIterator
struct ComplexInstrumentLegIterator {

    const std::byte* current = nullptr;

    const ComplexInstrumentDefinitionExpandedMessage* complex_instrument_definition_expanded_message = nullptr;

    std::uint8_t leg_count = 0;
    std::uint8_t entry_index = 0;
    const std::byte* entry = nullptr;

    // initialize iterator
    void initialize(const std::byte* data) {

        current = data;

        complex_instrument_definition_expanded_message = ComplexInstrumentDefinitionExpandedMessage::parse(current);
        current += sizeof(ComplexInstrumentDefinitionExpandedMessage);

        leg_count = complex_instrument_definition_expanded_message->leg_count.get();
        entry_index = 0;
        entry = nullptr;
    }

    // next entry
    bool next() {

        if (entry_index >= leg_count) {
            return false;
        }

        entry = current;
        entry_index++;

        return true;
    }

    // advance past processed entry
    void advance(std::size_t bytes) {
        current += bytes;
    }

    // reset iterator
    void reset() {
        current = nullptr;

        complex_instrument_definition_expanded_message = nullptr;

        leg_count = 0;
        entry_index = 0;
        entry = nullptr;
    }
};
}
