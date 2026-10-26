#pragma once

#include "../types/Text.hpp"
#include "../structs/SimpleBinaryHeader.hpp"

namespace cme::mdp3::v8 {

#pragma pack(push, 1)

// AdminLogout
struct AdminLogout {

    Text text;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint16_t message_type = 16;

    // parse method
    static AdminLogout* parse(std::byte* buffer) {
        return reinterpret_cast<AdminLogout*>(buffer);
    }

    // parse method const
    static const AdminLogout* parse(const std::byte* buffer) {
        return reinterpret_cast<const AdminLogout*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const AdminLogout* parse(const SimpleBinaryHeader* header) {
        return reinterpret_cast<const AdminLogout*>(reinterpret_cast<const std::byte*>(header) + sizeof(SimpleBinaryHeader));
    }
};

#pragma pack(pop)
}
