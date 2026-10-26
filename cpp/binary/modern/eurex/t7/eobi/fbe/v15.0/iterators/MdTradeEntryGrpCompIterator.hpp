#pragma once

#include "../definitions.hpp"

namespace eurex::t7::eobi::fbe::v15_0 {
// MdTradeEntryGrpCompIterator
struct MdTradeEntryGrpCompIterator {

    const std::byte* current = nullptr;

    const TradeReversal* trade_reversal = nullptr;

    std::uint8_t no_md_entries = 0;
    std::uint8_t entry_index = 0;
    const std::byte* entry = nullptr;

    // initialize iterator
    void initialize(const std::byte* data) {

        current = data;

        trade_reversal = TradeReversal::parse(current);
        current += sizeof(TradeReversal);

        no_md_entries = trade_reversal->no_md_entries.get();
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

        trade_reversal = nullptr;

        no_md_entries = 0;
        entry_index = 0;
        entry = nullptr;
    }
};
}
