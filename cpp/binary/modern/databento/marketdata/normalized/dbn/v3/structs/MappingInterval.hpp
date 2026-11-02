#pragma once

#include "../types/StartDate.hpp"
#include "../types/EndDate.hpp"
#include "../types/MappedSymbol.hpp"

namespace databento::marketdata::normalized::dbn::v3 {

#pragma pack(push, 1)

struct MappingInterval {

    StartDate start_date;
    EndDate end_date;
    MappedSymbol mapped_symbol;

    // parse method
    static MappingInterval* parse(std::byte* buffer) {
        return reinterpret_cast<MappingInterval*>(buffer);
    }

    // parse method const
    static const MappingInterval* parse(const std::byte* buffer) {
        return reinterpret_cast<const MappingInterval*>(buffer);
    }
};

#pragma pack(pop)
}
