#pragma once

#include "../types/ClientAppVersionLength.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1 {

#pragma pack(push, 1)

struct ClientAppVersion {

    ClientAppVersionLength client_app_version_length;

    // parse method
    static ClientAppVersion* parse(std::byte* buffer) {
        return reinterpret_cast<ClientAppVersion*>(buffer);
    }

    // parse method const
    static const ClientAppVersion* parse(const std::byte* buffer) {
        return reinterpret_cast<const ClientAppVersion*>(buffer);
    }
};

#pragma pack(pop)
}
