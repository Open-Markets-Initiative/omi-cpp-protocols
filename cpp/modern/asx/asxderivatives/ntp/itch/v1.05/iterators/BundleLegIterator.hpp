#pragma once

#include "../definitions.hpp"

namespace asx::asxderivatives::ntp::itch::v1_05 {
// BundleLegIterator
struct BundleLegIterator {

    // the entry count Bundle Leg states
    static constexpr std::size_t count = 20;

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
