#pragma once

#include "../definitions.hpp"

namespace eurex::t7::eobi::fbe::v3_0 {
// InstrmtLegGrpCompIterator
struct InstrmtLegGrpCompIterator {

    const std::byte* current = nullptr;

    const AddComplexInstrument* add_complex_instrument = nullptr;

    std::uint8_t no_legs = 0;
    std::uint8_t entry_index = 0;
    const std::byte* entry = nullptr;

    // initialize iterator
    void initialize(const std::byte* data) {

        current = data;

        add_complex_instrument = AddComplexInstrument::parse(current);
        current += sizeof(AddComplexInstrument);

        no_legs = add_complex_instrument->no_legs.get();
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

        add_complex_instrument = nullptr;

        no_legs = 0;
        entry_index = 0;
        entry = nullptr;
    }
};
}
