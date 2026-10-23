#pragma once

#include "../types/EncodingType.hpp"
#include "../types/MessageSequenceNumber.hpp"
#include "../types/TcpSendingTime.hpp"
#include "../types/TcpMessageSize.hpp"

namespace cme::mdp3::v13 {

#pragma pack(push, 1)

struct ClientTechnicalHeader {

    EncodingType encoding_type;
    MessageSequenceNumber message_sequence_number;
    TcpSendingTime tcp_sending_time;
    TcpMessageSize tcp_message_size;

    // parse method
    static ClientTechnicalHeader* parse(std::byte* buffer) {
        return reinterpret_cast<ClientTechnicalHeader*>(buffer);
    }

    // parse method const
    static const ClientTechnicalHeader* parse(const std::byte* buffer) {
        return reinterpret_cast<const ClientTechnicalHeader*>(buffer);
    }
};

#pragma pack(pop)
}
