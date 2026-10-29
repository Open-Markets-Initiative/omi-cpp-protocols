#pragma once

#include "../structs/InboundBusinessHeader.hpp"
#include "../types/MassActionType.hpp"
#include "../types/MassActionScope.hpp"
#include "../types/Clordid.hpp"
#include "../types/MassCancelRestatementReason.hpp"
#include "../types/Ordtagid.hpp"
#include "../types/SideOptional.hpp"
#include "../types/Offset31Padding1.hpp"
#include "../types/Asset.hpp"
#include "../types/SecurityIdOptional.hpp"
#include "../structs/InvestorId.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0 {

#pragma pack(push, 1)

// OrderMassActionRequestMessage
struct OrderMassActionRequestMessage {

    InboundBusinessHeader inbound_business_header;
    MassActionType mass_action_type;
    MassActionScope mass_action_scope;
    Clordid clordid;
    MassCancelRestatementReason mass_cancel_restatement_reason;
    Ordtagid ordtagid;
    SideOptional side_optional;
    Offset31Padding1 offset_31_padding_1;
    Asset asset;
    SecurityIdOptional security_id_optional;
    InvestorId investor_id;

    // parse method
    static OrderMassActionRequestMessage* parse(std::byte* buffer) {
        return reinterpret_cast<OrderMassActionRequestMessage*>(buffer);
    }

    // parse method const
    static const OrderMassActionRequestMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const OrderMassActionRequestMessage*>(buffer);
    }
};

#pragma pack(pop)
}
