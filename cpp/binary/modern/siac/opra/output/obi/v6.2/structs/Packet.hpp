#pragma once

#include "../structs/BlockHeader.hpp"

namespace siac::opra::output::obi::v6_2 {

#pragma pack(push, 1)

struct Packet {

    BlockHeader block_header;

    // parse method
    static Packet* parse(std::byte* buffer) {
        return reinterpret_cast<Packet*>(buffer);
    }

    // parse method const
    static const Packet* parse(const std::byte* buffer) {
        return reinterpret_cast<const Packet*>(buffer);
    }
};

#pragma pack(pop)
}
