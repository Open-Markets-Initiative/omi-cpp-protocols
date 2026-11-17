// B3.B3Derivatives.BinaryUmdf.Sbe.v1.9: structs/GroupSizeEncoding.hpp
#pragma once

#include "../types/BlockLength.hpp"
#include "../types/NumInGroup.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v1_9 {

#pragma pack(push, 1)

struct GroupSizeEncoding {

    BlockLength block_length;
    NumInGroup num_in_group;

    // parse method
    static GroupSizeEncoding* parse(std::byte* buffer) {
        return reinterpret_cast<GroupSizeEncoding*>(buffer);
    }

    // parse method const
    static const GroupSizeEncoding* parse(const std::byte* buffer) {
        return reinterpret_cast<const GroupSizeEncoding*>(buffer);
    }
};

#pragma pack(pop)
}
