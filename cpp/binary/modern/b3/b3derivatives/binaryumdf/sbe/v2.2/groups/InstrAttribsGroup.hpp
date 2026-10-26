#pragma once

#include "../types/InstrAttribType.hpp"
#include "../types/InstrAttribValue.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v2_2 {

#pragma pack(push, 1)

struct InstrAttribsGroup {

    InstrAttribType instr_attrib_type;
    InstrAttribValue instr_attrib_value;

    // parse method
    static InstrAttribsGroup* parse(std::byte* buffer) {
        return reinterpret_cast<InstrAttribsGroup*>(buffer);
    }

    // parse method const
    static const InstrAttribsGroup* parse(const std::byte* buffer) {
        return reinterpret_cast<const InstrAttribsGroup*>(buffer);
    }
};

#pragma pack(pop)
}
