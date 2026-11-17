// Cboe.C1Options.MarketDataFeed.Csm.v1.4.2: iterators/SettlementValueMdEntryIterator.hpp
#pragma once

#include "../definitions.hpp"

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {
// SettlementValueMdEntryIterator
struct SettlementValueMdEntryIterator {

    const std::byte* current = nullptr;

    const SettlementValueMessage* settlement_value_message = nullptr;

    std::uint8_t no_entries = 0;
    std::uint8_t entry_index = 0;
    const std::byte* entry = nullptr;

    // initialize iterator
    void initialize(const std::byte* data) {

        current = data;

        settlement_value_message = SettlementValueMessage::parse(current);
        current += sizeof(SettlementValueMessage);

        no_entries = settlement_value_message->no_entries.get();
        entry_index = 0;
        entry = nullptr;
    }

    // next entry
    bool next() {

        if (entry_index >= no_entries) {
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

        settlement_value_message = nullptr;

        no_entries = 0;
        entry_index = 0;
        entry = nullptr;
    }
};
}
