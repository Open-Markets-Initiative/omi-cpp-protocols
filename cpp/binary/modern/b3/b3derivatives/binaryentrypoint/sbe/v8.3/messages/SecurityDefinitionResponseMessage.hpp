#pragma once

#include "../structs/OutboundBusinessHeader.hpp"
#include "../types/Offset18Padding2.hpp"
#include "../types/SecurityReqId.hpp"
#include "../types/SecurityIdOptional.hpp"
#include "../types/SecurityResponseType.hpp"
#include "../types/SecurityStrategyType.hpp"
#include "../types/Symbol.hpp"
#include "../types/SecurityResponseId.hpp"
#include "../types/SenderLocation.hpp"
#include "../types/EnteringTrader.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3 {

#pragma pack(push, 1)

// SecurityDefinitionResponseMessage
struct SecurityDefinitionResponseMessage {

    OutboundBusinessHeader outbound_business_header;
    Offset18Padding2 offset_18_padding_2;
    SecurityReqId security_req_id;
    SecurityIdOptional security_id_optional;
    SecurityResponseType security_response_type;
    SecurityStrategyType security_strategy_type;
    Symbol symbol;
    SecurityResponseId security_response_id;
    SenderLocation sender_location;
    EnteringTrader entering_trader;

    // parse method
    static SecurityDefinitionResponseMessage* parse(std::byte* buffer) {
        return reinterpret_cast<SecurityDefinitionResponseMessage*>(buffer);
    }

    // parse method const
    static const SecurityDefinitionResponseMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const SecurityDefinitionResponseMessage*>(buffer);
    }
};

#pragma pack(pop)
}
