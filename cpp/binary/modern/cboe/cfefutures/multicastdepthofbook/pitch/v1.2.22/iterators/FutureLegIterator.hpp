#pragma once

#include "../definitions.hpp"

namespace cboe::cfefutures::multicastdepthofbook::pitch::v1_2_22 {
// FutureLegIterator
struct FutureLegIterator {

    const std::byte* current = nullptr;

    const FuturesInstrumentDefinitionMessage* futures_instrument_definition_message = nullptr;

    std::uint8_t leg_count = 0;
    std::uint8_t entry_index = 0;
    const std::byte* entry = nullptr;

    // initialize iterator
    void initialize(const std::byte* data) {

        current = data;

        futures_instrument_definition_message = FuturesInstrumentDefinitionMessage::parse(current);
        current += sizeof(FuturesInstrumentDefinitionMessage);

        leg_count = futures_instrument_definition_message->leg_count.get();
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

        futures_instrument_definition_message = nullptr;

        leg_count = 0;
        entry_index = 0;
        entry = nullptr;
    }
};
}
