// Databento.MarketData.Normalized.Dbn.v1: messages/ErrorMsg.hpp
#pragma once

#include "../types/Err.hpp"

namespace databento::marketdata::normalized::dbn::v1 {

#pragma pack(push, 1)

// An error message from the Databento Live Subscription Gateway (LSG)
struct ErrorMsg {

    Err err;

    // parse method
    static ErrorMsg* parse(std::byte* buffer) {
        return reinterpret_cast<ErrorMsg*>(buffer);
    }

    // parse method const
    static const ErrorMsg* parse(const std::byte* buffer) {
        return reinterpret_cast<const ErrorMsg*>(buffer);
    }
};

#pragma pack(pop)
}
