#pragma once

#include "../definitions.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v2_2 {
// InstrAttribsGroupIterator
struct InstrAttribsGroupIterator {

    const std::byte* current = nullptr;

    const GroupSizeEncoding* group_size_encoding = nullptr;

    std::uint16_t block_length = 0;
    std::uint8_t num_in_group = 0;
    std::uint8_t entry_index = 0;
    const std::byte* entry = nullptr;

    // initialize group iterator
    void initialize(const std::byte* data) {

        current = data;

        group_size_encoding = GroupSizeEncoding::parse(current);
        current += sizeof(GroupSizeEncoding);

        block_length = group_size_encoding->block_length.get();
        num_in_group = group_size_encoding->num_in_group.get();
        entry_index = 0;
        entry = nullptr;
    }

    // next entry
    bool next() {

        if (entry_index >= num_in_group) {
            return false;
        }

        entry = current;
        entry_index++;
        current += block_length;

        return true;
    }

    // reset iterator
    void reset() {
        current = nullptr;

        group_size_encoding = nullptr;

        block_length = 0;
        num_in_group = 0;
        entry_index = 0;
        entry = nullptr;
    }
};
}
