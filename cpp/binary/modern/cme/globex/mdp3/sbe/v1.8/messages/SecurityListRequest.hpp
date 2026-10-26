#pragma once

#include "../types/MdReqId.hpp"
#include "../types/SubscriptionReqType.hpp"
#include "../structs/SimpleBinaryHeader.hpp"

namespace cme::mdp3::v8 {

#pragma pack(push, 1)

// SecurityListRequest
struct SecurityListRequest {

    MdReqId md_req_id;
    SubscriptionReqType subscription_req_type;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint16_t message_type = 208;

    // parse method
    static SecurityListRequest* parse(std::byte* buffer) {
        return reinterpret_cast<SecurityListRequest*>(buffer);
    }

    // parse method const
    static const SecurityListRequest* parse(const std::byte* buffer) {
        return reinterpret_cast<const SecurityListRequest*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const SecurityListRequest* parse(const SimpleBinaryHeader* header) {
        return reinterpret_cast<const SecurityListRequest*>(reinterpret_cast<const std::byte*>(header) + sizeof(SimpleBinaryHeader));
    }
};

#pragma pack(pop)
}
