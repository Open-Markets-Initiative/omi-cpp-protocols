#pragma once

#include "../types/Side.hpp"
#include "../types/Account.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0 {

#pragma pack(push, 1)

struct SidesGroup {

    Side side;
    Account account;

    // parse method
    static SidesGroup* parse(std::byte* buffer) {
        return reinterpret_cast<SidesGroup*>(buffer);
    }

    // parse method const
    static const SidesGroup* parse(const std::byte* buffer) {
        return reinterpret_cast<const SidesGroup*>(buffer);
    }
};

#pragma pack(pop)
}
