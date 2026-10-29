#pragma once

#include "../types/DeskIdLength.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1 {

#pragma pack(push, 1)

struct DeskId {

    DeskIdLength desk_id_length;

    // parse method
    static DeskId* parse(std::byte* buffer) {
        return reinterpret_cast<DeskId*>(buffer);
    }

    // parse method const
    static const DeskId* parse(const std::byte* buffer) {
        return reinterpret_cast<const DeskId*>(buffer);
    }
};

#pragma pack(pop)
}
