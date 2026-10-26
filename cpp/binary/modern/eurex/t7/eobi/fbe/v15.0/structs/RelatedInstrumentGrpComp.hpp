#pragma once

#include "../types/RelatedSecurityId.hpp"

namespace eurex::t7::eobi::fbe::v15_0 {

#pragma pack(push, 1)

struct RelatedInstrumentGrpComp {

    RelatedSecurityId related_security_id;

    // parse method
    static RelatedInstrumentGrpComp* parse(std::byte* buffer) {
        return reinterpret_cast<RelatedInstrumentGrpComp*>(buffer);
    }

    // parse method const
    static const RelatedInstrumentGrpComp* parse(const std::byte* buffer) {
        return reinterpret_cast<const RelatedInstrumentGrpComp*>(buffer);
    }
};

#pragma pack(pop)
}
