#pragma once

#include "../definitions.hpp"

namespace cme::mdp3::v13 {
// ClientTcpFrameIterator
struct ClientTcpFrameIterator {

    const std::byte* current = nullptr;
    const std::byte* end = nullptr;

    const ClientTechnicalHeader* client_technical_header = nullptr;
    const MessageHeader* message_header = nullptr;
    std::uint16_t template_id = 0;
    std::uint16_t message_size = 0;
    const std::byte* message = nullptr;

    // initialize over reassembled byte stream
    void initialize(const std::byte* data, std::size_t bytes) {
        current = data;
        end = data + bytes;

        client_technical_header = nullptr;
        message_header = nullptr;
        message = nullptr;
        template_id = 0;
        message_size = 0;
    }

    // next reassembled packet
    bool next() {

        if (current >= end) {
            return false;
        }

        if (current + sizeof(ClientTechnicalHeader) + sizeof(MessageHeader) > end) {
            return false;
        }

        client_technical_header = ClientTechnicalHeader::parse(current);
        message_header = MessageHeader::parse(current + sizeof(ClientTechnicalHeader));
        message = current + sizeof(ClientTechnicalHeader) + sizeof(MessageHeader);

        template_id = message_header->simple_binary_header.template_id.get();
        message_size = message_header->message_size.get();

        current += message_size + 14;

        return true;
    }

    // reset iterator
    void reset() {
        current = nullptr;
        end = nullptr;

        client_technical_header = nullptr;
        message_header = nullptr;
        message = nullptr;
        template_id = 0;
        message_size = 0;
    }
};
}
