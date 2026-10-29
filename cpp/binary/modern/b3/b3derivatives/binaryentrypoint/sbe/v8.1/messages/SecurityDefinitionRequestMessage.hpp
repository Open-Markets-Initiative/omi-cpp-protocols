#pragma once

#include "../structs/InboundBusinessHeader.hpp"
#include "../types/SecurityReqId.hpp"
#include "../types/SenderLocation.hpp"
#include "../types/EnteringTrader.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1 {

#pragma pack(push, 1)

// SecurityDefinitionRequestMessage
struct SecurityDefinitionRequestMessage {

    InboundBusinessHeader inbound_business_header;
    SecurityReqId security_req_id;
    SenderLocation sender_location;
    EnteringTrader entering_trader;

    // parse method
    static SecurityDefinitionRequestMessage* parse(std::byte* buffer) {
        return reinterpret_cast<SecurityDefinitionRequestMessage*>(buffer);
    }

    // parse method const
    static const SecurityDefinitionRequestMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const SecurityDefinitionRequestMessage*>(buffer);
    }
};

#pragma pack(pop)
}
