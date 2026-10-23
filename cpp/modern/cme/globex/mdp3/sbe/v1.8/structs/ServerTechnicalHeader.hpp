#pragma once

#include "../types/EncodingType.hpp"
#include "../types/MessageSequenceNumber.hpp"
#include "../types/TcpSendingTime.hpp"
#include "../types/TcpMessageSize.hpp"

namespace cme::mdp3::v8 {

#pragma pack(push, 1)

struct ServerTechnicalHeader {

    EncodingType encoding_type;
    MessageSequenceNumber message_sequence_number;
    TcpSendingTime tcp_sending_time;
    TcpMessageSize tcp_message_size;

    // parse method
    static ServerTechnicalHeader* parse(std::byte* buffer) {
        return reinterpret_cast<ServerTechnicalHeader*>(buffer);
    }

    // parse method const
    static const ServerTechnicalHeader* parse(const std::byte* buffer) {
        return reinterpret_cast<const ServerTechnicalHeader*>(buffer);
    }
};

#pragma pack(pop)
}
