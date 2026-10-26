#pragma once

#include "../types/TransactTime.hpp"
#include "../types/QuoteReqId.hpp"
#include "../bitfields/MatchEventIndicator.hpp"
#include "../types/Padding3.hpp"
#include "../structs/SimpleBinaryHeader.hpp"

namespace cme::mdp3::v9 {

#pragma pack(push, 1)

// QuoteRequest
struct QuoteRequest {

    TransactTime transact_time;
    QuoteReqId quote_req_id;
    MatchEventIndicator match_event_indicator;
    Padding3 padding_3;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint16_t message_type = 39;

    // parse method
    static QuoteRequest* parse(std::byte* buffer) {
        return reinterpret_cast<QuoteRequest*>(buffer);
    }

    // parse method const
    static const QuoteRequest* parse(const std::byte* buffer) {
        return reinterpret_cast<const QuoteRequest*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const QuoteRequest* parse(const SimpleBinaryHeader* header) {
        return reinterpret_cast<const QuoteRequest*>(reinterpret_cast<const std::byte*>(header) + sizeof(SimpleBinaryHeader));
    }
};

#pragma pack(pop)
}
