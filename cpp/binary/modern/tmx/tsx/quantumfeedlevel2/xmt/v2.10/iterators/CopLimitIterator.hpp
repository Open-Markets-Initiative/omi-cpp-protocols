#pragma once

#include "../definitions.hpp"

namespace tmx::tsx::quantumfeedlevel2::xmt::v2_10 {
// CopLimitIterator
struct CopLimitIterator {

    // the entry count Cop Limit states
    static constexpr std::size_t count = 15;

    const std::byte* current = nullptr;
    std::size_t entry_index = 0;
    const std::byte* entry = nullptr;

    // initialize iterator
    void initialize(const std::byte* data) {
        current = data;
        entry_index = 0;
        entry = nullptr;
    }

    // next entry
    bool next() {

        if (entry_index >= count) {
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
        entry_index = 0;
        entry = nullptr;
    }
};
}
