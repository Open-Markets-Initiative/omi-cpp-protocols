// Nasdaq.NsmEquities.TotalView.Itch.v5.0.2026: messages/LoginRejectedPacket.hpp
#pragma once

#include "../types/RejectReasonCode.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2026 {

#pragma pack(push, 1)

// The SoupBinTCP server sends this packet in response to an invalid Login Request Packet from the client
struct LoginRejectedPacket {

    RejectReasonCode reject_reason_code;

    // parse method
    static LoginRejectedPacket* parse(std::byte* buffer) {
        return reinterpret_cast<LoginRejectedPacket*>(buffer);
    }

    // parse method const
    static const LoginRejectedPacket* parse(const std::byte* buffer) {
        return reinterpret_cast<const LoginRejectedPacket*>(buffer);
    }
};

#pragma pack(pop)
}
