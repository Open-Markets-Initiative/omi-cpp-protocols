#pragma once

#include "../types/RequestTime.hpp"
#include "../types/SecurityId.hpp"
#include "../structs/OrderDetailsComp.hpp"
#include "../structs/MessageHeaderComp.hpp"

namespace eurex::t7::eobi::fbe::v13_0 {

#pragma pack(push, 1)

// 
struct OrderAdd {

    RequestTime request_time;
    SecurityId security_id;
    OrderDetailsComp order_details_comp;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint16_t message_type = 13100;

    // parse method
    static OrderAdd* parse(std::byte* buffer) {
        return reinterpret_cast<OrderAdd*>(buffer);
    }

    // parse method const
    static const OrderAdd* parse(const std::byte* buffer) {
        return reinterpret_cast<const OrderAdd*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const OrderAdd* parse(const MessageHeaderComp* header) {
        return reinterpret_cast<const OrderAdd*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeaderComp));
    }
};

#pragma pack(pop)
}
