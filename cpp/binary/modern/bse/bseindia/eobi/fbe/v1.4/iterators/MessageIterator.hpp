#pragma once

#include "../definitions.hpp"

namespace bse::bseindia::eobi::fbe::v1_4 {
// MessageIterator
struct MessageIterator {

    const std::byte* current = nullptr;
    const std::byte* end = nullptr;

    const PacketHeader* packet_header = nullptr;

    std::uint16_t template_id = 0;
    std::uint16_t body_len = 0;
    const std::byte* message = nullptr;

    // initialize parser
    void initialize(const std::byte* data, std::size_t length) {

        end = data + length;

        if (length < sizeof(PacketHeader)) {
            current = end;
            message = nullptr;
            packet_header = nullptr;
            template_id = 0;
            body_len = 0;
            return;
        }

        packet_header = PacketHeader::parse(data);
        current = data + sizeof(PacketHeader);
        message = nullptr;

        template_id = 0;
        body_len = 0;
    }

    // next message
    bool next() {

        if (current >= end) {
            return false;
        }

        if (current + sizeof(MessageHeader) > end) {
            return false;
        }

        const auto* header = MessageHeader::parse(current);
        message = current + sizeof(MessageHeader);

        template_id = header->template_id.get();
        body_len = header->body_len.get();

        current += body_len;

        return true;
    }

    // reset iterator
    void reset() {
        current = nullptr;
        end = nullptr;

        packet_header = nullptr;
        message = nullptr;
        template_id = 0;
        body_len = 0;
    }
};
}
