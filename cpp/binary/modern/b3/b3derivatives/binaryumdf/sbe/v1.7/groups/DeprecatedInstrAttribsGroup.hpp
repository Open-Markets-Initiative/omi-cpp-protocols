#pragma once

#include "../types/InstrAttribType.hpp"
#include "../types/InstrAttribValue.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v1_7 {

#pragma pack(push, 1)

struct DeprecatedInstrAttribsGroup {

    InstrAttribType instr_attrib_type;
    InstrAttribValue instr_attrib_value;

    // parse method
    static DeprecatedInstrAttribsGroup* parse(std::byte* buffer) {
        return reinterpret_cast<DeprecatedInstrAttribsGroup*>(buffer);
    }

    // parse method const
    static const DeprecatedInstrAttribsGroup* parse(const std::byte* buffer) {
        return reinterpret_cast<const DeprecatedInstrAttribsGroup*>(buffer);
    }
};

#pragma pack(pop)
}
