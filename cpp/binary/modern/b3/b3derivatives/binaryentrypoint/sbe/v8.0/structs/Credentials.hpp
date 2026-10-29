#pragma once

#include "../types/CredentialsLength.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0 {

#pragma pack(push, 1)

struct Credentials {

    CredentialsLength credentials_length;

    // parse method
    static Credentials* parse(std::byte* buffer) {
        return reinterpret_cast<Credentials*>(buffer);
    }

    // parse method const
    static const Credentials* parse(const std::byte* buffer) {
        return reinterpret_cast<const Credentials*>(buffer);
    }
};

#pragma pack(pop)
}
