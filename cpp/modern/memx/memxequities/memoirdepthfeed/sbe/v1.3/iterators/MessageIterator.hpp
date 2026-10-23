#pragma once

#include "../definitions.hpp"

namespace memx::memxequities::memoirdepthfeed::sbe::v1_3 {
// MessageIterator
struct MessageIterator {

    const std::byte* current = nullptr;
    const std::byte* end = nullptr;

    const SequencedMessage* sequenced_message = nullptr;
    const Message* message_header = nullptr;

    std::uint16_t message_count = 0;
    std::uint16_t message_index = 0;
    std::uint8_t template_id = 0;
    std::uint16_t message_length = 0;
    const std::byte* message = nullptr;

    // initialize parser
    void initialize(const std::byte* data, std::size_t length) {

        end = data + length;

        if (length < sizeof(SequencedMessage)) {
            current = end;
            message = nullptr;
            message_count = 0;
            return;
        }

        current = data;
        message = nullptr;

        sequenced_message = SequencedMessage::parse(current);
        current += sizeof(SequencedMessage);

        message_header = nullptr;
        message_index = 0;
        template_id = 0;
        message_length = 0;
        message_count = sequenced_message->message_count.get();
    }

    // next message
    bool next() {

        if (message_index >= message_count) {
            return false;
        }

        if (current + sizeof(Message) + sizeof(SbeHeader) > end) {
            return false;
        }

        message_index++;

        message_header = Message::parse(current);
        // the code sits in the header behind this one
        const auto* code = SbeHeader::parse(current + sizeof(Message));
        message = current + sizeof(Message) + sizeof(SbeHeader);

        template_id = code->template_id.get();
        message_length = message_header->message_length.get();

        current += message_length + 2;

        return true;
    }

    // reset iterator
    void reset() {
        current = nullptr;
        end = nullptr;

        sequenced_message = nullptr;
        message_header = nullptr;

        message = nullptr;
        message_count = 0;
        message_index = 0;
        template_id = 0;
        message_length = 0;
    }
};
}
