#pragma once

#include "../types/HeartBtInt.hpp"
#include "../structs/SimpleBinaryHeader.hpp"

namespace cme::mdp3::v5 {

#pragma pack(push, 1)

// AdminLogin
struct AdminLogin {

    HeartBtInt heart_bt_int;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint16_t message_type = 15;

    // parse method
    static AdminLogin* parse(std::byte* buffer) {
        return reinterpret_cast<AdminLogin*>(buffer);
    }

    // parse method const
    static const AdminLogin* parse(const std::byte* buffer) {
        return reinterpret_cast<const AdminLogin*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const AdminLogin* parse(const SimpleBinaryHeader* header) {
        return reinterpret_cast<const AdminLogin*>(reinterpret_cast<const std::byte*>(header) + sizeof(SimpleBinaryHeader));
    }
};

#pragma pack(pop)
}
