#pragma once

#include "../types/Err.hpp"
#include "../types/ErrorCode.hpp"
#include "../types/IsLast.hpp"

namespace databento::marketdata::normalized::dbn::v2 {

#pragma pack(push, 1)

// An error message from the Databento Live Subscription Gateway (LSG)
struct ErrorMsg {

    Err err;
    ErrorCode error_code;
    IsLast is_last;

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
