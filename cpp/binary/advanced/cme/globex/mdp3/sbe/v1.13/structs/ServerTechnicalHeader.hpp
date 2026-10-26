#pragma once

#include <cstddef>
#include "../types/EncodingType.hpp"
#include "../types/MessageSequenceNumber.hpp"
#include "../types/TcpSendingTime.hpp"

namespace cme::mdp3::v13 {

namespace sbe_mdp3 = ::cme::mdp3::v13;

#pragma pack(push, 1)

struct server_technical_header {

    sbe_mdp3::encoding_type encoding_type;
    sbe_mdp3::message_sequence_number message_sequence_number;
    sbe_mdp3::tcp_sending_time tcp_sending_time;

    // parse method
    static server_technical_header* parse(std::byte* buffer) {
        return reinterpret_cast<server_technical_header*>(buffer);
    }

    // parse method const
    static const server_technical_header* parse(const std::byte* buffer) {
        return reinterpret_cast<const server_technical_header*>(buffer);
    }
};

// layout verification
static_assert(offsetof(server_technical_header, encoding_type) == 0, "unexpected offset of server_technical_header::encoding_type");
static_assert(offsetof(server_technical_header, message_sequence_number) == 2, "unexpected offset of server_technical_header::message_sequence_number");
static_assert(offsetof(server_technical_header, tcp_sending_time) == 6, "unexpected offset of server_technical_header::tcp_sending_time");
static_assert(sizeof(server_technical_header) == 14, "unexpected sizeof server_technical_header");

#pragma pack(pop)
}
