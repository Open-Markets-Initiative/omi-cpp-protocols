// Cboe.C1Options.MarketDataFeed.Csm.v1.4.2: iterators/MdEntryIterator.hpp
#pragma once

#include "../definitions.hpp"

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {
// MdEntryIterator
struct MdEntryIterator {

    const std::byte* current = nullptr;

    const CurrentMarketRefreshMessage* current_market_refresh_message = nullptr;

    std::uint8_t no_entries = 0;
    std::uint8_t entry_index = 0;
    const std::byte* entry = nullptr;

    // initialize iterator
    void initialize(const std::byte* data) {

        current = data;

        current_market_refresh_message = CurrentMarketRefreshMessage::parse(current);
        current += sizeof(CurrentMarketRefreshMessage);

        no_entries = current_market_refresh_message->no_entries.get();
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

        current_market_refresh_message = nullptr;

        no_entries = 0;
        entry_index = 0;
        entry = nullptr;
    }
};
}
