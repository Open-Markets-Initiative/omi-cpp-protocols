#pragma once

#include "../types/LogoutReason.hpp"

namespace miax::miaxoptions::topofmarket::mach::v2_5 {

#pragma pack(push, 1)

struct LogoutRequest {

    LogoutReason logout_reason;

    // parse method
    static LogoutRequest* parse(std::byte* buffer) {
        return reinterpret_cast<LogoutRequest*>(buffer);
    }

    // parse method const
    static const LogoutRequest* parse(const std::byte* buffer) {
        return reinterpret_cast<const LogoutRequest*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const LogoutRequest* parse(const SesmPacketHeader* header) {
        return reinterpret_cast<const LogoutRequest*>(reinterpret_cast<const std::byte*>(header) + sizeof(SesmPacketHeader));
    }
};

#pragma pack(pop)
}
