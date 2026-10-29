#pragma once

#include "../definitions.hpp"

namespace bse::bseindia::eobi::fbe::v1_4 {
// MdInstrumentEntryGrpIterator
struct MdInstrumentEntryGrpIterator {

    const std::byte* current = nullptr;

    const InstrumentSummaryMessage* instrument_summary_message = nullptr;

    std::uint8_t no_md_entries = 0;
    std::uint8_t entry_index = 0;
    const std::byte* entry = nullptr;

    // initialize iterator
    void initialize(const std::byte* data) {

        current = data;

        instrument_summary_message = InstrumentSummaryMessage::parse(current);
        current += sizeof(InstrumentSummaryMessage);

        no_md_entries = instrument_summary_message->no_md_entries.get();
        entry_index = 0;
        entry = nullptr;
    }

    // next entry
    bool next() {

        if (entry_index >= no_md_entries) {
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

        instrument_summary_message = nullptr;

        no_md_entries = 0;
        entry_index = 0;
        entry = nullptr;
    }
};
}
