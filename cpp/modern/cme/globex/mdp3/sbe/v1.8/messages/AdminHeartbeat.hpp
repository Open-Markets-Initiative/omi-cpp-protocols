#pragma once

#include "../structs/SimpleBinaryHeader.hpp"

namespace cme::mdp3::v8 {

#pragma pack(push, 1)

// AdminHeartbeat
struct AdminHeartbeat {


    // the type code that selects this message in the dispatch switch
    static constexpr std::uint16_t message_type = 12;

    // parse method
    static AdminHeartbeat* parse(std::byte* buffer) {
        return reinterpret_cast<AdminHeartbeat*>(buffer);
    }

    // parse method const
    static const AdminHeartbeat* parse(const std::byte* buffer) {
        return reinterpret_cast<const AdminHeartbeat*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const AdminHeartbeat* parse(const SimpleBinaryHeader* header) {
        return reinterpret_cast<const AdminHeartbeat*>(reinterpret_cast<const std::byte*>(header) + sizeof(SimpleBinaryHeader));
    }
};

#pragma pack(pop)
}
