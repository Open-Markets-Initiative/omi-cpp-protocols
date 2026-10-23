#pragma once

#include "../types/MdReqId.hpp"
#include "../types/SubscriptionReqType.hpp"
#include "../types/MdReqIdStatus.hpp"
#include "../structs/MessageHeader.hpp"

namespace cme::mdp3::v13 {

#pragma pack(push, 1)

// RequestAck
struct RequestAck {

    MdReqId md_req_id;
    SubscriptionReqType subscription_req_type;
    MdReqIdStatus md_req_id_status;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint16_t message_type = 206;

    // parse method
    static RequestAck* parse(std::byte* buffer) {
        return reinterpret_cast<RequestAck*>(buffer);
    }

    // parse method const
    static const RequestAck* parse(const std::byte* buffer) {
        return reinterpret_cast<const RequestAck*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const RequestAck* parse(const MessageHeader* header) {
        return reinterpret_cast<const RequestAck*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
