#pragma once

#include "../types/ControlFields.hpp"

namespace databento::marketdata::normalized::dbn::v1 {

#pragma pack(push, 1)

struct AuthenticationResponse {

    ControlFields control_fields;

    // parse method
    static AuthenticationResponse* parse(std::byte* buffer) {
        return reinterpret_cast<AuthenticationResponse*>(buffer);
    }

    // parse method const
    static const AuthenticationResponse* parse(const std::byte* buffer) {
        return reinterpret_cast<const AuthenticationResponse*>(buffer);
    }
};

#pragma pack(pop)
}
