// Asx.AsxDerivatives.Ntp.Itch.v1.05: iterators/BundleLegIterator.hpp
#pragma once

#include "../definitions.hpp"

namespace asx::asxderivatives::ntp::itch::v1_05 {
// BundleLegIterator
struct BundleLegIterator {

    const std::byte* current = nullptr;

    const BundlesSymbolDirectory* bundles_symbol_directory = nullptr;

    std::uint8_t legs = 0;
    std::uint8_t entry_index = 0;
    const std::byte* entry = nullptr;

    // initialize iterator
    void initialize(const std::byte* data) {

        current = data;

        bundles_symbol_directory = BundlesSymbolDirectory::parse(current);
        current += sizeof(BundlesSymbolDirectory);

        legs = bundles_symbol_directory->legs.get();
        entry_index = 0;
        entry = nullptr;
    }

    // next entry
    bool next() {

        if (entry_index >= legs) {
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

        bundles_symbol_directory = nullptr;

        legs = 0;
        entry_index = 0;
        entry = nullptr;
    }
};
}
