#pragma once

#include "../types/MdReqIdOptional.hpp"
#include "../types/MdReqRejReason.hpp"
#include "../types/Text.hpp"
#include "../structs/SimpleBinaryHeader.hpp"

namespace cme::mdp3::v8 {

#pragma pack(push, 1)

// RequestReject
struct RequestReject {

    MdReqIdOptional md_req_id_optional;
    MdReqRejReason md_req_rej_reason;
    Text text;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint16_t message_type = 207;

    // parse method
    static RequestReject* parse(std::byte* buffer) {
        return reinterpret_cast<RequestReject*>(buffer);
    }

    // parse method const
    static const RequestReject* parse(const std::byte* buffer) {
        return reinterpret_cast<const RequestReject*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const RequestReject* parse(const SimpleBinaryHeader* header) {
        return reinterpret_cast<const RequestReject*>(reinterpret_cast<const std::byte*>(header) + sizeof(SimpleBinaryHeader));
    }
};

#pragma pack(pop)
}
