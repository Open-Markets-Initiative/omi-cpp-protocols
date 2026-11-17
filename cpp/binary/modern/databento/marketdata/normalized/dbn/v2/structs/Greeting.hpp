// Databento.MarketData.Normalized.Dbn.v2: structs/Greeting.hpp
#pragma once

#include "../types/ControlFields.hpp"

namespace databento::marketdata::normalized::dbn::v2 {

#pragma pack(push, 1)

struct Greeting {

    ControlFields control_fields;

    // parse method
    static Greeting* parse(std::byte* buffer) {
        return reinterpret_cast<Greeting*>(buffer);
    }

    // parse method const
    static const Greeting* parse(const std::byte* buffer) {
        return reinterpret_cast<const Greeting*>(buffer);
    }
};

#pragma pack(pop)
}
