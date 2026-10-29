#pragma once

#include "../types/ClientIpLength.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1 {

#pragma pack(push, 1)

struct ClientIp {

    ClientIpLength client_ip_length;

    // parse method
    static ClientIp* parse(std::byte* buffer) {
        return reinterpret_cast<ClientIp*>(buffer);
    }

    // parse method const
    static const ClientIp* parse(const std::byte* buffer) {
        return reinterpret_cast<const ClientIp*>(buffer);
    }
};

#pragma pack(pop)
}
