#pragma once

#include "../types/EncodingType.hpp"
#include "../types/MessageSequenceNumber.hpp"
#include "../types/TcpSendingTime.hpp"

namespace cme::mdp3::v5 {

#pragma pack(push, 1)

struct ServerTechnicalHeader {

    EncodingType encoding_type;
    MessageSequenceNumber message_sequence_number;
    TcpSendingTime tcp_sending_time;

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
