#pragma once

#include "../types/SecurityId.hpp"
#include "../types/LastQty.hpp"
#include "../types/Side.hpp"
#include "../types/Pad3.hpp"
#include "../types/TransactTime.hpp"
#include "../structs/MessageHeaderComp.hpp"

namespace eurex::t7::eobi::fbe::v3_0 {

#pragma pack(push, 1)

// 
struct QuoteRequest {

    SecurityId security_id;
    LastQty last_qty;
    Side side;
    Pad3 pad3;
    TransactTime transact_time;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint16_t message_type = 13503;

    // parse method
    static QuoteRequest* parse(std::byte* buffer) {
        return reinterpret_cast<QuoteRequest*>(buffer);
    }

    // parse method const
    static const QuoteRequest* parse(const std::byte* buffer) {
        return reinterpret_cast<const QuoteRequest*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const QuoteRequest* parse(const MessageHeaderComp* header) {
        return reinterpret_cast<const QuoteRequest*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeaderComp));
    }
};

#pragma pack(pop)
}
