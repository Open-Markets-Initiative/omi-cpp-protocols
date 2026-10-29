#pragma once

#include "../definitions.hpp"

namespace bse::bseindia::eobi::fbe::v1_4 {
// InstrmtLegGrpIterator
struct InstrmtLegGrpIterator {

    const std::byte* current = nullptr;

    const AddComplexInstrumentMessage* add_complex_instrument_message = nullptr;

    std::uint8_t no_legs = 0;
    std::uint8_t entry_index = 0;
    const std::byte* entry = nullptr;

    // initialize iterator
    void initialize(const std::byte* data) {

        current = data;

        add_complex_instrument_message = AddComplexInstrumentMessage::parse(current);
        current += sizeof(AddComplexInstrumentMessage);

        no_legs = add_complex_instrument_message->no_legs.get();
        entry_index = 0;
        entry = nullptr;
    }

    // next entry
    bool next() {

        if (entry_index >= no_legs) {
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

        add_complex_instrument_message = nullptr;

        no_legs = 0;
        entry_index = 0;
        entry = nullptr;
    }
};
}
