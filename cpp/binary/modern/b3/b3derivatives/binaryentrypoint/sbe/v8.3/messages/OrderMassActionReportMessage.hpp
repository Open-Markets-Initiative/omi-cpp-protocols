#pragma once

#include "../structs/OutboundBusinessHeader.hpp"
#include "../types/MassActionType.hpp"
#include "../types/MassActionScope.hpp"
#include "../types/Clordid.hpp"
#include "../types/MassActionReportId.hpp"
#include "../types/TransactTime.hpp"
#include "../types/MassActionResponse.hpp"
#include "../types/MassActionRejectReason.hpp"
#include "../types/MassCancelRestatementReason.hpp"
#include "../types/Ordtagid.hpp"
#include "../types/SideOptional.hpp"
#include "../types/Offset49Padding1.hpp"
#include "../types/Asset.hpp"
#include "../types/SecurityIdOptional.hpp"
#include "../structs/InvestorId.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3 {

#pragma pack(push, 1)

// OrderMassActionReportMessage
struct OrderMassActionReportMessage {

    OutboundBusinessHeader outbound_business_header;
    MassActionType mass_action_type;
    MassActionScope mass_action_scope;
    Clordid clordid;
    MassActionReportId mass_action_report_id;
    TransactTime transact_time;
    MassActionResponse mass_action_response;
    MassActionRejectReason mass_action_reject_reason;
    MassCancelRestatementReason mass_cancel_restatement_reason;
    Ordtagid ordtagid;
    SideOptional side_optional;
    Offset49Padding1 offset_49_padding_1;
    Asset asset;
    SecurityIdOptional security_id_optional;
    InvestorId investor_id;

    // parse method
    static OrderMassActionReportMessage* parse(std::byte* buffer) {
        return reinterpret_cast<OrderMassActionReportMessage*>(buffer);
    }

    // parse method const
    static const OrderMassActionReportMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const OrderMassActionReportMessage*>(buffer);
    }
};

#pragma pack(pop)
}
