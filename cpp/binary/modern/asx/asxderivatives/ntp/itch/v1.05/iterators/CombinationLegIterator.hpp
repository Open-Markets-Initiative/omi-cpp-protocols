// Asx.AsxDerivatives.Ntp.Itch.v1.05: iterators/CombinationLegIterator.hpp
#pragma once

#include "../definitions.hpp"

namespace asx::asxderivatives::ntp::itch::v1_05 {
// CombinationLegIterator
struct CombinationLegIterator {

    const std::byte* current = nullptr;

    const CombinationSymbolDirectoryMessage* combination_symbol_directory_message = nullptr;

    std::uint8_t legs = 0;
    std::uint8_t entry_index = 0;
    const std::byte* entry = nullptr;

    // initialize iterator
    void initialize(const std::byte* data) {

        current = data;

        combination_symbol_directory_message = CombinationSymbolDirectoryMessage::parse(current);
        current += sizeof(CombinationSymbolDirectoryMessage);

        legs = combination_symbol_directory_message->legs.get();
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

        combination_symbol_directory_message = nullptr;

        legs = 0;
        entry_index = 0;
        entry = nullptr;
    }
};
}
