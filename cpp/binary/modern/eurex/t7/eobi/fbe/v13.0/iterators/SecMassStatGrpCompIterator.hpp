#pragma once

#include "../definitions.hpp"

namespace eurex::t7::eobi::fbe::v13_0 {
// SecMassStatGrpCompIterator
struct SecMassStatGrpCompIterator {

    const std::byte* current = nullptr;

    const MassInstrumentStateChange* mass_instrument_state_change = nullptr;

    std::uint8_t no_related_sym = 0;
    std::uint8_t entry_index = 0;
    const std::byte* entry = nullptr;

    // initialize iterator
    void initialize(const std::byte* data) {

        current = data;

        mass_instrument_state_change = MassInstrumentStateChange::parse(current);
        current += sizeof(MassInstrumentStateChange);

        no_related_sym = mass_instrument_state_change->no_related_sym.get();
        entry_index = 0;
        entry = nullptr;
    }

    // next entry
    bool next() {

        if (entry_index >= no_related_sym) {
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

        mass_instrument_state_change = nullptr;

        no_related_sym = 0;
        entry_index = 0;
        entry = nullptr;
    }
};
}
