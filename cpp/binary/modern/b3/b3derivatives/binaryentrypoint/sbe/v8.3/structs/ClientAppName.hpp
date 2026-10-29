#pragma once

#include "../types/ClientAppNameLength.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3 {

#pragma pack(push, 1)

struct ClientAppName {

    ClientAppNameLength client_app_name_length;

    // parse method
    static ClientAppName* parse(std::byte* buffer) {
        return reinterpret_cast<ClientAppName*>(buffer);
    }

    // parse method const
    static const ClientAppName* parse(const std::byte* buffer) {
        return reinterpret_cast<const ClientAppName*>(buffer);
    }
};

#pragma pack(pop)
}
