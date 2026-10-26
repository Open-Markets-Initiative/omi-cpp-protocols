#pragma once

#include "../definitions.hpp"

namespace lseg::lse::level2mbo::gtp::v26_2 {
// MessageIterator
struct MessageIterator {

    const std::byte* current = nullptr;
    const std::byte* end = nullptr;

    const UnitHeader* unit_header = nullptr;
    const MessageHeader* message_header = nullptr;

    std::uint8_t message_count = 0;
    std::uint8_t message_index = 0;
    std::uint8_t message_type = 0;
    std::uint16_t message_length = 0;
    const std::byte* message = nullptr;

    // initialize parser
    void initialize(const std::byte* data, std::size_t length) {

        end = data + length;

        if (length < sizeof(UnitHeader)) {
            current = end;
            message = nullptr;
            message_count = 0;
            return;
        }

        current = data;
        message = nullptr;

        unit_header = UnitHeader::parse(current);
        current += sizeof(UnitHeader);

        message_header = nullptr;
        message_index = 0;
        message_type = 0;
        message_length = 0;
        message_count = unit_header->message_count.get();
    }

    // next message
    bool next() {

        if (message_index >= message_count) {
            return false;
        }

        if (current + sizeof(MessageHeader) > end) {
            return false;
        }

        message_index++;

        message_header = MessageHeader::parse(current);
        message = current + sizeof(MessageHeader);

        message_type = message_header->message_type.get();
        message_length = message_header->message_length.get();

        current += message_length;

        return true;
    }

    // reset iterator
    void reset() {
        current = nullptr;
        end = nullptr;

        unit_header = nullptr;
        message_header = nullptr;

        message = nullptr;
        message_count = 0;
        message_index = 0;
        message_type = 0;
        message_length = 0;
    }
};
}
