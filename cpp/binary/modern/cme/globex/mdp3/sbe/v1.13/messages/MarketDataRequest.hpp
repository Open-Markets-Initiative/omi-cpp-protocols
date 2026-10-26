#pragma once

#include "../types/MdReqId.hpp"
#include "../types/SubscriptionReqType.hpp"
#include "../structs/SimpleBinaryHeader.hpp"

namespace cme::mdp3::v13 {

#pragma pack(push, 1)

// MarketDataRequest
struct MarketDataRequest {

    MdReqId md_req_id;
    SubscriptionReqType subscription_req_type;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint16_t message_type = 205;

    // parse method
    static MarketDataRequest* parse(std::byte* buffer) {
        return reinterpret_cast<MarketDataRequest*>(buffer);
    }

    // parse method const
    static const MarketDataRequest* parse(const std::byte* buffer) {
        return reinterpret_cast<const MarketDataRequest*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const MarketDataRequest* parse(const SimpleBinaryHeader* header) {
        return reinterpret_cast<const MarketDataRequest*>(reinterpret_cast<const std::byte*>(header) + sizeof(SimpleBinaryHeader));
    }
};

#pragma pack(pop)
}
