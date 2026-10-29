#pragma once

#include "../definitions.hpp"

namespace nasdaq::iseoptions::ordercombofeed::itch::v1_1 {
// LegInformationIterator
struct LegInformationIterator {

    const std::byte* current = nullptr;

    const ComplexStrategyDirectoryMessage* complex_strategy_directory_message = nullptr;

    std::uint8_t number_of_legs = 0;
    std::uint8_t entry_index = 0;
    const std::byte* entry = nullptr;

    // initialize iterator
    void initialize(const std::byte* data) {

        current = data;

        complex_strategy_directory_message = ComplexStrategyDirectoryMessage::parse(current);
        current += sizeof(ComplexStrategyDirectoryMessage);

        number_of_legs = complex_strategy_directory_message->number_of_legs.get();
        entry_index = 0;
        entry = nullptr;
    }

    // next entry
    bool next() {

        if (entry_index >= number_of_legs) {
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

        complex_strategy_directory_message = nullptr;

        number_of_legs = 0;
        entry_index = 0;
        entry = nullptr;
    }
};
}
