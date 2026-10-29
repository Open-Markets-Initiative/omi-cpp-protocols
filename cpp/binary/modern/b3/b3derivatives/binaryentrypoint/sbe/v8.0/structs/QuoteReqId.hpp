#pragma once

#include "../types/QuoteReqIdLength.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0 {

#pragma pack(push, 1)

struct QuoteReqId {

    QuoteReqIdLength quote_req_id_length;

    // parse method
    static QuoteReqId* parse(std::byte* buffer) {
        return reinterpret_cast<QuoteReqId*>(buffer);
    }

    // parse method const
    static const QuoteReqId* parse(const std::byte* buffer) {
        return reinterpret_cast<const QuoteReqId*>(buffer);
    }
};

#pragma pack(pop)
}
