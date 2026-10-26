#pragma once

#include "../types/RequestTime.hpp"
#include "../types/TransactTime.hpp"
#include "../types/PrevDisplayQty.hpp"
#include "../types/SecurityId.hpp"
#include "../structs/OrderDetailsComp.hpp"
#include "../structs/MessageHeaderComp.hpp"

namespace eurex::t7::eobi::fbe::v13_0 {

#pragma pack(push, 1)

// 
struct OrderModifySamePrio {

    RequestTime request_time;
    TransactTime transact_time;
    PrevDisplayQty prev_display_qty;
    SecurityId security_id;
    OrderDetailsComp order_details_comp;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint16_t message_type = 13106;

    // parse method
    static OrderModifySamePrio* parse(std::byte* buffer) {
        return reinterpret_cast<OrderModifySamePrio*>(buffer);
    }

    // parse method const
    static const OrderModifySamePrio* parse(const std::byte* buffer) {
        return reinterpret_cast<const OrderModifySamePrio*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const OrderModifySamePrio* parse(const MessageHeaderComp* header) {
        return reinterpret_cast<const OrderModifySamePrio*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeaderComp));
    }
};

#pragma pack(pop)
}
