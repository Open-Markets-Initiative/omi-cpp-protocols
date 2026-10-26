#pragma once

#include "../definitions.hpp"

namespace siac::cqs::output::cta::v2_10_a {
// MessageIterator
struct MessageIterator {

    const std::byte* current = nullptr;
    const std::byte* end = nullptr;

    const BlockHeader* block_header = nullptr;
    const Message* message_header = nullptr;

    std::uint8_t messages_in_block = 0;
    std::uint8_t message_index = 0;
    char message_category = 0;
    std::uint16_t message_length = 0;
    const std::byte* message = nullptr;

    // initialize parser
    void initialize(const std::byte* data, std::size_t length) {

        end = data + length;

        if (length < sizeof(BlockHeader)) {
            current = end;
            message = nullptr;
            messages_in_block = 0;
            return;
        }

        current = data;
        message = nullptr;

        block_header = BlockHeader::parse(current);
        current += sizeof(BlockHeader);

        message_header = nullptr;
        message_index = 0;
        message_category = 0;
        message_length = 0;
        messages_in_block = block_header->messages_in_block.get();
    }

    // next message
    bool next() {

        if (message_index >= messages_in_block) {
            return false;
        }

        if (current + sizeof(Message) > end) {
            return false;
        }

        message_index++;

        message_header = Message::parse(current);
        message = current + sizeof(Message);

        message_category = message_header->message_category.get();
        message_length = message_header->message_length.get();

        current += message_length;

        return true;
    }

    // reset iterator
    void reset() {
        current = nullptr;
        end = nullptr;

        block_header = nullptr;
        message_header = nullptr;

        message = nullptr;
        messages_in_block = 0;
        message_index = 0;
        message_category = 0;
        message_length = 0;
    }
};
}
